#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exportadorpdf.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextEdit>

// Soporte básico para .docx: extraer texto plano del XML interno
#include <QTemporaryDir>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_analizador(new Analizador(this))
{
    ui->setupUi(this);
    setWindowTitle("Analizador de Reuniones Grabadas");
    habilitarExportacion(false);

    // Márgenes del layout principal
    ui->layoutPrincipal->setContentsMargins(12, 12, 12, 12);
    ui->layoutPrincipal->setSpacing(8);
    ui->layoutControles->setContentsMargins(8, 8, 8, 8);

    ui->statusbar->showMessage("Listo. Carga una transcripcion para comenzar.");

    connect(m_analizador, &Analizador::analisisCompleto,
            this, &MainWindow::onAnalisisCompleto);
    connect(m_analizador, &Analizador::error,
            this, &MainWindow::onError);
    connect(m_analizador, &Analizador::progreso,
            this, &MainWindow::onProgreso);
}

MainWindow::~MainWindow() {
    delete ui;
}

// ---------------------------------------------------------------------------
// Slots de botones
// ---------------------------------------------------------------------------

void MainWindow::on_btnCargarArchivo_clicked()
{
    QString ruta = QFileDialog::getOpenFileName(
        this,
        "Cargar transcripción",
        QString(),
        "Archivos de texto (*.txt *.docx)"
    );

    if (ruta.isEmpty()) return;

    QString contenido = leerArchivo(ruta);
    if (contenido.isEmpty()) {
        QMessageBox::warning(this, "Archivo vacío", "No se pudo leer contenido del archivo.");
        return;
    }

    ui->txtTranscripcion->setPlainText(contenido);
    ui->statusbar->showMessage("Archivo cargado: " + ruta);
    habilitarExportacion(false);
}

void MainWindow::on_btnAnalizar_clicked()
{
    QString transcripcion = ui->txtTranscripcion->toPlainText().trimmed();
    QString tema = ui->txtTema->text().trimmed();
    QString apiKey = ui->txtApiKey->text().trimmed();

    if (transcripcion.isEmpty()) {
        QMessageBox::warning(this, "Sin transcripción",
                             "Primero cargá o escribí la transcripción de la reunión.");
        return;
    }
    if (tema.isEmpty()) {
        QMessageBox::warning(this, "Sin tema",
                             "Ingresá el tema de la reunión.");
        return;
    }
    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "Sin API Key",
                             "Ingresá tu API Key de OpenAI.");
        return;
    }

    m_tema = tema;
    ui->btnAnalizar->setEnabled(false);
    ui->btnAnalizar->setText("Analizando...");
    habilitarExportacion(false);

    // Limpiar resultados anteriores
    ui->txtActa->clear();
    ui->txtResumen->clear();
    ui->txtTareas->clear();

    m_analizador->analizar(transcripcion, tema, apiKey);
}

void MainWindow::on_btnExportarPDF_clicked()
{
    if (m_ultimoResultado.acta.isEmpty()) {
        QMessageBox::warning(this, "Sin resultados",
                             "Primero analizá una reunión antes de exportar.");
        return;
    }
    ExportadorPDF::exportar(m_tema, m_ultimoResultado, this);
}

// ---------------------------------------------------------------------------
// Slots del analizador
// ---------------------------------------------------------------------------

void MainWindow::onAnalisisCompleto(const ResultadoAnalisis &resultado)
{
    m_ultimoResultado = resultado;

    ui->txtResumen->setPlainText(resultado.resumenEjecutivo);
    ui->txtActa->setPlainText(resultado.acta);
    ui->txtTareas->setPlainText(resultado.tareasPorParticipante);

    // Mostrar participantes detectados en la barra de estado
    QString participantes = resultado.participantes.join(", ");
    ui->statusbar->showMessage("Análisis completo. Participantes: " + participantes);

    ui->btnAnalizar->setEnabled(true);
    ui->btnAnalizar->setText("Analizar");
    habilitarExportacion(true);

    // Ir a la pestaña de resultados
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::onError(const QString &mensaje)
{
    QMessageBox::critical(this, "Error", mensaje);
    ui->btnAnalizar->setEnabled(true);
    ui->btnAnalizar->setText("Analizar");
    ui->statusbar->showMessage("Error en el análisis.");
}

void MainWindow::onProgreso(const QString &mensaje)
{
    ui->statusbar->showMessage(mensaje);
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

void MainWindow::habilitarExportacion(bool habilitar)
{
    ui->btnExportarPDF->setEnabled(habilitar);
}

QString MainWindow::leerArchivo(const QString &ruta) const
{
    if (ruta.endsWith(".txt", Qt::CaseInsensitive)) {
        QFile f(ruta);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return {};
        QTextStream in(&f);
        in.setEncoding(QStringConverter::Utf8);
        return in.readAll();
    }

    if (ruta.endsWith(".docx", Qt::CaseInsensitive)) {
        // Un .docx es un ZIP. Extraemos word/document.xml y limpiamos las tags.
        QTemporaryDir tmpDir;
        if (!tmpDir.isValid()) return {};

        // Usar unzip del sistema (disponible en Windows con Qt o en Linux/Mac)
        QProcess proc;
        proc.start("unzip", {"-o", ruta, "word/document.xml", "-d", tmpDir.path()});
        proc.waitForFinished(5000);

        QString xmlPath = tmpDir.path() + "/word/document.xml";
        QFile xmlFile(xmlPath);
        if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return {};
        }

        QString xmlContent = QTextStream(&xmlFile).readAll();

        // Eliminar todas las tags XML y dejar sólo el texto
        QString texto;
        bool dentroDeTag = false;
        bool espacioAntes = false;
        for (const QChar &c : xmlContent) {
            if (c == '<') {
                dentroDeTag = true;
                if (!espacioAntes && !texto.isEmpty()) {
                    texto += ' ';
                    espacioAntes = true;
                }
            } else if (c == '>') {
                dentroDeTag = false;
            } else if (!dentroDeTag) {
                texto += c;
                espacioAntes = false;
            }
        }

        // Limpiar espacios múltiples
        texto = texto.simplified();
        return texto;
    }

    return {};
}
