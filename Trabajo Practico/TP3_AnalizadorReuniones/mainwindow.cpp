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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_algoritmo(new AnalizadorGemini(this))  // polimorfismo: AnalizadorGemini* -> AlgoritmoIA*
{
    ui->setupUi(this);
    setWindowTitle("Analizador de Reuniones — " + m_algoritmo->nombreProveedor());
    setAcceptDrops(true);
    habilitarExportacion(false);

    ui->statusbar->showMessage("Listo. Carga una transcripcion para comenzar.");

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
    QString apiKey        = ui->txtApiKey->text().trimmed();

    if (transcripcion.isEmpty()) {
        QMessageBox::warning(this, "Sin transcripcion",
                             "Primero carga o escribe la transcripcion de la reunion.");
        return;
    }
    if (tema.isEmpty()) {
        QMessageBox::warning(this, "Sin tema", "Ingresa el tema de la reunion.");
        return;
    }
    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "Sin API Key", "Ingresa tu API Key de Gemini.");
        return;
    }

    m_tema = tema;
    ui->btnAnalizar->setEnabled(false);
    ui->btnAnalizar->setText("ANALIZANDO...");
    habilitarExportacion(false);
    ui->txtActa->clear();
    ui->txtResumen->clear();
    ui->txtTareas->clear();

    // Llamada polimorfica: m_algoritmo es AlgoritmoIA*, pero ejecuta AnalizadorGemini::analizar
    m_algoritmo->analizar(transcripcion, tema, apiKey);
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

// ---------------------------------------------------------------------------
// Helpers privados
// ---------------------------------------------------------------------------

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
        QString("Analisis en esta sesion: %1  |  Participantes totales vistos: %2")
            .arg(total)
            .arg(DataManager::instancia().todosLosParticipantes().size())
    );
}
