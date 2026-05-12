#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analizador.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCargarArchivo_clicked();
    void on_btnAnalizar_clicked();
    void on_btnExportarPDF_clicked();

    void onAnalisisCompleto(const ResultadoAnalisis &resultado);
    void onError(const QString &mensaje);
    void onProgreso(const QString &mensaje);

private:
    Ui::MainWindow *ui;
    Analizador *m_analizador;
    ResultadoAnalisis m_ultimoResultado;
    QString m_tema;

    void habilitarExportacion(bool habilitar);
    QString leerArchivo(const QString &ruta) const;
};

#endif // MAINWINDOW_H
