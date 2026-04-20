#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ventanasecundaria.h" // Incluimos la nueva ventana

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
    void on_btnIngresar_clicked();
    void on_apiResponse(QNetworkReply* reply); // Slot para recibir el clima

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    VentanaSecundaria *nuevaVentana; // Puntero a la segunda ventana
};

#endif // MAINWINDOW_H