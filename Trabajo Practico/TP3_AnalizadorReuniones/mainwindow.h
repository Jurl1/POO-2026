#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// =============================================================================
// MainWindow — Responsabilidad unica: visualizacion e interaccion con el usuario
//
// NO contiene logica de IA ni de exportacion.
// Trabaja con un puntero AlgoritmoIA* (polimorfismo):
// no sabe ni le importa si adentro hay Gemini u otro proveedor.
// =============================================================================

#include <QMainWindow>
#include "algoritmoIA.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // Soporte para drag & drop de archivos
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void on_btnCargarArchivo_clicked();
    void on_btnAnalizar_clicked();
    void on_btnExportarPDF_clicked();

    // Slots conectados a las senales de AlgoritmoIA (interfaz abstracta)
    void onAnalisisCompleto(const ResultadoAnalisis &resultado);
    void onError(const QString &mensaje);
    void onProgreso(const QString &mensaje);

private:
    Ui::MainWindow  *ui;
    AlgoritmoIA     *m_algoritmo;    // puntero a clase abstracta: polimorfismo
    ResultadoAnalisis m_ultimoResultado;
    QString           m_tema;

    void cargarArchivo(const QString &ruta);
    QString leerTxt(const QString &ruta) const;
    QString leerDocx(const QString &ruta) const;
    void habilitarExportacion(bool habilitar);
    void actualizarEstadisticas();
};

#endif // MAINWINDOW_H
