#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// =============================================================================
// MainWindow — Responsabilidad única: visualización e interacción con el usuario
//
// NO contiene lógica de IA ni de exportación.
// Trabaja con un puntero AlgoritmoIA* (polimorfismo):
// no sabe ni le importa si adentro hay Gemini u otro proveedor.
// Recibe el token JWT, la API key y el usuario desde LoginWindow.
// =============================================================================

#include <QMainWindow>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include "algoritmoIA.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &token, const QString &apiKey, const QString &usuario, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // Soporte para drag & drop de archivos
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void on_btnCargarArchivo_clicked();
    void on_btnAnalizar_clicked();
    void on_btnExportarPDF_clicked();

    // Slots de Historial
    void on_btnRefrescarHistorial_clicked();
    void on_listHistorial_currentRowChanged(int currentRow);
    void on_btnExportarHistorialPDF_clicked();
    void on_tabWidget_currentChanged(int index);

    // Slots de Perfil
    void on_btnGuardarApiKey_clicked();
    void on_btnCerrarSesion_clicked();

    // Slots conectados a las señales de AlgoritmoIA (interfaz abstracta)
    void onAnalisisCompleto(const ResultadoAnalisis &resultado);
    void onError(const QString &mensaje);
    void onProgreso(const QString &mensaje);

private:
    Ui::MainWindow  *ui;
    AlgoritmoIA     *m_algoritmo;    // puntero a clase abstracta: polimorfismo
    ResultadoAnalisis m_ultimoResultado;
    QString           m_tema;
    QString           m_token;
    QString           m_apiKey;
    QString           m_usuario;

    // Datos de Historial
    QJsonArray        m_historialServidor;
    ResultadoAnalisis m_resultadoHistorialSeleccionado;
    QString           m_temaHistorialSeleccionado;
    QNetworkAccessManager *m_historialNetManager;

    void refrescarHistorialServidor();
    void cargarArchivo(const QString &ruta);
    QString leerTxt(const QString &ruta) const;
    QString leerDocx(const QString &ruta) const;
    void habilitarExportacion(bool habilitar);
    void actualizarEstadisticas();
};

#endif // MAINWINDOW_H
