#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analizadorgemini.h"
#include "exportadorpdf.h"
#include "datamanager.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QTemporaryDir>
#include <QProcess>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "loginwindow.h"

MainWindow::MainWindow(const QString &token, const QString &apiKey, const QString &usuario, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_algoritmo(new AnalizadorGemini(this))  // polimorfismo: AnalizadorGemini* -> AlgoritmoIA*
    , m_token(token)
    , m_apiKey(apiKey)
    , m_usuario(usuario)
    , m_historialNetManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    setWindowTitle("Analizador de Reuniones — Usuario: " + m_usuario + " (" + m_algoritmo->nombreProveedor() + ")");
    setAcceptDrops(true);
    habilitarExportacion(false);

    // Ocultar campo de API Key de la UI ya que viene de la cuenta del usuario
    ui->lblApiKey->hide();
    ui->txtApiKey->hide();

    // Mostrar datos del usuario en la pestaña de Perfil
    ui->lblPerfilUsuario->setText("Usuario: " + m_usuario);

    // Asegurar que abra en la pestaña de Transcripción
    ui->tabWidget->setCurrentIndex(0);

    // Configurar el token JWT en DataManager para peticiones al backend
    DataManager::instancia().setToken(m_token);

    ui->statusbar->showMessage("Sesión iniciada como " + m_usuario + ". Cargá una transcripción para comenzar.");

    // Conectar cambio de pestaña principal
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);

    // Las conexiones son a AlgoritmoIA (interfaz), no a AnalizadorGemini directamente
    connect(m_algoritmo, &AlgoritmoIA::analisisCompleto, this, &MainWindow::onAnalisisCompleto);
    connect(m_algoritmo, &AlgoritmoIA::error,            this, &MainWindow::onError);
    connect(m_algoritmo, &AlgoritmoIA::progreso,         this, &MainWindow::onProgreso);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------------------------------------------------------------------
// Drag & Drop
// ---------------------------------------------------------------------------

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        const QList<QUrl> urls = event->mimeData()->urls();
        for (const QUrl &url : urls) {
            QString path = url.toLocalFile().toLower();
            if (path.endsWith(".txt") || path.endsWith(".docx")) {
                event->acceptProposedAction();
                ui->lblDropHint->setText("Suelta el archivo para cargarlo...");
                return;
            }
        }
    }
    event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    ui->lblDropHint->setText("Arrastra un archivo .txt o .docx aqui, o usa el boton");
    const QList<QUrl> urls = event->mimeData()->urls();
    if (!urls.isEmpty()) {
        cargarArchivo(urls.first().toLocalFile());
    }
}

// ---------------------------------------------------------------------------
// Slots de botones
// ---------------------------------------------------------------------------

void MainWindow::on_btnCargarArchivo_clicked()
{
    QString ruta = QFileDialog::getOpenFileName(
        this, "Cargar transcripcion", QString(),
        "Archivos de texto (*.txt *.docx)"
    );
    if (!ruta.isEmpty()) cargarArchivo(ruta);
}

void MainWindow::on_btnAnalizar_clicked()
{
    QString transcripcion = ui->txtTranscripcion->toPlainText().trimmed();
    QString tema          = ui->txtTema->text().trimmed();

    if (transcripcion.isEmpty()) {
        QMessageBox::warning(this, "Sin transcripcion",
                             "Primero carga o escribe la transcripcion de la reunion.");
        return;
    }
    if (tema.isEmpty()) {
        QMessageBox::warning(this, "Sin tema", "Ingresa el tema de la reunion.");
        return;
    }
    if (m_apiKey.isEmpty()) {
        QMessageBox::critical(this, "Sin API Key", "No se encontró la API Key asociada a tu usuario.");
        return;
    }

    m_tema = tema;
    ui->btnAnalizar->setEnabled(false);
    ui->btnAnalizar->setText("ANALIZANDO...");
    habilitarExportacion(false);
    ui->txtActa->clear();
    ui->txtResumen->clear();
    ui->txtTareas->clear();

    // Llamada polimórfica pasándole la m_apiKey obtenida en el login
    m_algoritmo->analizar(transcripcion, tema, m_apiKey);
}

void MainWindow::on_btnExportarPDF_clicked()
{
    if (!m_ultimoResultado.valido) {
        QMessageBox::warning(this, "Sin resultados", "Primero analiza una reunion.");
        return;
    }
    ExportadorPDF::exportar(m_tema, m_ultimoResultado, this);
}

// ---------------------------------------------------------------------------
// Slots de AlgoritmoIA
// ---------------------------------------------------------------------------

void MainWindow::onAnalisisCompleto(const ResultadoAnalisis &resultado)
{
    m_ultimoResultado = resultado;

    ui->txtResumen->setPlainText(resultado.resumenEjecutivo);
    ui->txtActa->setPlainText(resultado.acta);
    ui->txtTareas->setPlainText(resultado.tareasPorParticipante);

    // Enviar al VPS MySQL remoto (incluye header Authorization con m_token)
    DataManager::instancia().enviarAlServidor(m_tema, resultado);

    actualizarEstadisticas();

    ui->btnAnalizar->setEnabled(true);
    ui->btnAnalizar->setText("ANALIZAR CON GEMINI");
    habilitarExportacion(true);
    ui->tabWidget->setCurrentIndex(1);
    ui->tabResultadosInterno->setCurrentIndex(0);  // ir a sub-pestaña Resumen

    ui->statusbar->showMessage(
        "Analisis completo. Participantes: " + resultado.participantes.join(", ")
    );
}

void MainWindow::onError(const QString &mensaje)
{
    QMessageBox::critical(this, "Error", mensaje);
    ui->btnAnalizar->setEnabled(true);
    ui->btnAnalizar->setText("ANALIZAR CON GEMINI");
    ui->statusbar->showMessage("Error en el analisis.");
}

void MainWindow::onProgreso(const QString &mensaje)
{
    ui->statusbar->showMessage(mensaje);
}

#include <QFileInfo>

void MainWindow::cargarArchivo(const QString &ruta)
{
    QString contenido;
    if (ruta.endsWith(".txt", Qt::CaseInsensitive))
        contenido = leerTxt(ruta);
    else if (ruta.endsWith(".docx", Qt::CaseInsensitive))
        contenido = leerDocx(ruta);

    if (contenido.isEmpty()) {
        QMessageBox::warning(this, "Archivo vacio", "No se pudo leer contenido del archivo.");
        return;
    }

    ui->txtTranscripcion->setPlainText(contenido);

    // Extraer el nombre del archivo sin extensión y ponerlo en el tema de la reunión
    QFileInfo info(ruta);
    ui->txtTema->setText(info.completeBaseName());

    ui->statusbar->showMessage("Archivo cargado: " + ruta);
    ui->tabWidget->setCurrentIndex(0);
    habilitarExportacion(false);
}

QString MainWindow::leerTxt(const QString &ruta) const
{
    QFile f(ruta);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return {};
    QTextStream in(&f);
    in.setEncoding(QStringConverter::Utf8);
    return in.readAll();
}

QString MainWindow::leerDocx(const QString &ruta) const
{
    // Un .docx es un ZIP. Extraemos word/document.xml y limpiamos las tags XML.
    QTemporaryDir tmpDir;
    if (!tmpDir.isValid()) return {};

    QProcess proc;
    proc.start("unzip", {"-o", ruta, "word/document.xml", "-d", tmpDir.path()});
    proc.waitForFinished(5000);

    QFile xmlFile(tmpDir.path() + "/word/document.xml");
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) return {};

    QString xmlContent = QTextStream(&xmlFile).readAll();

    // Eliminar tags XML
    QString texto;
    bool dentroTag = false;
    for (const QChar &c : xmlContent) {
        if      (c == '<')  { dentroTag = true;  if (!texto.isEmpty()) texto += ' '; }
        else if (c == '>')  { dentroTag = false; }
        else if (!dentroTag){ texto += c; }
    }
    return texto.simplified();
}

void MainWindow::habilitarExportacion(bool habilitar)
{
    ui->btnExportarPDF->setEnabled(habilitar);
}

void MainWindow::actualizarEstadisticas()
{
    // Usa DataManager para mostrar cuantos analisis se han hecho en la sesion
    int total = DataManager::instancia().cantidadAnalisis();
    ui->lblEstadisticas->setText(
        QString("Usuario: %1  |  Análisis en esta sesión: %2  |  Participantes vistos: %3")
            .arg(m_usuario)
            .arg(total)
            .arg(DataManager::instancia().todosLosParticipantes().size())
    );
}

// ---------------------------------------------------------------------------
// Historial del Servidor
// ---------------------------------------------------------------------------

void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Pestaña 2 es "HISTORIAL SERVIDOR"
    if (index == 2) {
        refrescarHistorialServidor();
    }
}

void MainWindow::on_btnRefrescarHistorial_clicked()
{
    refrescarHistorialServidor();
}

void MainWindow::refrescarHistorialServidor()
{
    ui->btnRefrescarHistorial->setEnabled(false);
    ui->lblTituloHistorial->setText("CARGANDO HISTORIAL DEL SERVIDOR...");

    QUrl url("https://poo.juriserver.website/historial");
    QNetworkRequest request(url);
    if (!m_token.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_token).toUtf8());
    }

    QNetworkReply *reply = m_historialNetManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        ui->btnRefrescarHistorial->setEnabled(true);
        ui->lblTituloHistorial->setText("REUNIONES GUARDADAS EN EL SERVIDOR REMOTO");

        if (reply->error() != QNetworkReply::NoError) {
            ui->statusbar->showMessage("Error al cargar historial del servidor: " + reply->errorString());
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        if (!doc.isArray()) return;

        m_historialServidor = doc.array();
        ui->listHistorial->clear();
        ui->txtHistorialResumen->clear();
        ui->txtHistorialActa->clear();
        ui->txtHistorialTareas->clear();
        ui->btnExportarHistorialPDF->setEnabled(false);

        for (const QJsonValue &val : m_historialServidor) {
            QJsonObject obj = val.toObject();
            QString tema  = obj["tema"].toString();
            QString fecha = obj["fecha"].toString();
            ui->listHistorial->addItem(tema + "\n  [" + fecha + "]");
        }

        ui->statusbar->showMessage(QString("Historial del servidor cargado: %1 reuniones.").arg(m_historialServidor.size()));
    });
}

void MainWindow::on_listHistorial_currentRowChanged(int currentRow)
{
    if (currentRow < 0 || currentRow >= m_historialServidor.size()) {
        ui->txtHistorialResumen->clear();
        ui->txtHistorialActa->clear();
        ui->txtHistorialTareas->clear();
        ui->btnExportarHistorialPDF->setEnabled(false);
        return;
    }

    QJsonObject obj = m_historialServidor[currentRow].toObject();
    m_temaHistorialSeleccionado = obj["tema"].toString();

    m_resultadoHistorialSeleccionado.resumenEjecutivo = obj["resumen"].toString();
    m_resultadoHistorialSeleccionado.acta = obj["acta"].toString();
    m_resultadoHistorialSeleccionado.tareasPorParticipante = obj["tareas"].toString();
    m_resultadoHistorialSeleccionado.participantes = obj["participantes"].toString().split(", ", Qt::SkipEmptyParts);
    m_resultadoHistorialSeleccionado.valido = true;

    ui->txtHistorialResumen->setPlainText(m_resultadoHistorialSeleccionado.resumenEjecutivo);
    ui->txtHistorialActa->setPlainText(m_resultadoHistorialSeleccionado.acta);
    ui->txtHistorialTareas->setPlainText(m_resultadoHistorialSeleccionado.tareasPorParticipante);
    ui->btnExportarHistorialPDF->setEnabled(true);
}

void MainWindow::on_btnExportarHistorialPDF_clicked()
{
    if (!m_resultadoHistorialSeleccionado.valido) return;
    ExportadorPDF::exportar(m_temaHistorialSeleccionado, m_resultadoHistorialSeleccionado, this);
}

// ---------------------------------------------------------------------------
// Perfil y Configuración
// ---------------------------------------------------------------------------

void MainWindow::on_btnGuardarApiKey_clicked()
{
    QString nuevaKey = ui->txtPerfilApiKey->text().trimmed();
    if (nuevaKey.isEmpty()) {
        ui->lblPerfilApiKeyError->setText("Ingresá una API Key válida.");
        return;
    }

    ui->lblPerfilApiKeyError->setText("Guardando en el servidor...");
    ui->btnGuardarApiKey->setEnabled(false);

    QJsonObject json;
    json["api_key"] = nuevaKey;

    QUrl url("https://poo.juriserver.website/update_key");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (!m_token.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_token).toUtf8());
    }

    QNetworkReply *reply = m_historialNetManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply, nuevaKey]() {
        reply->deleteLater();
        ui->btnGuardarApiKey->setEnabled(true);

        if (reply->error() != QNetworkReply::NoError) {
            ui->lblPerfilApiKeyError->setText("Error de conexión al actualizar la API Key.");
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();

        if (obj["status"].toString() == "ok") {
            m_apiKey = nuevaKey;
            ui->txtPerfilApiKey->clear();
            ui->lblPerfilApiKeyError->setText("✓ API Key actualizada correctamente en el servidor.");
            QMessageBox::information(this, "API Key Actualizada", "Tu nueva API Key de Gemini fue guardada encriptada en tu cuenta.");
        } else {
            ui->lblPerfilApiKeyError->setText(obj["error"].toString());
        }
    });
}

void MainWindow::on_btnCerrarSesion_clicked()
{
    QMessageBox::StandardButton res = QMessageBox::question(
        this,
        "Cerrar Sesión",
        "¿Estás seguro de que querés cerrar sesión?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (res == QMessageBox::Yes) {
        auto *login = new LoginWindow();
        login->show();
        this->close();
    }
}
