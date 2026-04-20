#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. Instanciar el manager y conectar la señal finished
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_apiResponse(QNetworkReply*)));

    // 2. Hacer la petición a la API.
    // Usamos Open-Meteo con las coordenadas exactas de la Ciudad de Córdoba.
    QNetworkRequest request(QUrl("https://api.open-meteo.com/v1/forecast?latitude=-31.4135&longitude=-64.1810&current_weather=true"));
    manager->get(request);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- Botón de Login ---
void MainWindow::on_btnIngresar_clicked()
{
    QString usuario = ui->lineEditUsuario->text();
    QString clave = ui->lineEditClave->text();

    if(usuario == "admin" && clave == "1234") {
        // Instanciamos y mostramos la segunda ventana
        nuevaVentana = new VentanaSecundaria();
        nuevaVentana->show();

        // Cerramos la ventana de login actual
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Credenciales incorrectas");
        ui->lineEditClave->clear();
    }
}

// --- Procesamiento de la API ---
void MainWindow::on_apiResponse(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError) {
        // Leemos la respuesta de internet
        QByteArray data = reply->readAll();

        // Convertimos el texto a un Documento JSON de Qt
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        // Entramos al bloque "current_weather" y sacamos la "temperature"
        QJsonObject current_weather = jsonObj["current_weather"].toObject();
        double temp = current_weather["temperature"].toDouble();

        // Lo mostramos en el Label (convertimos el double a texto)
        ui->labelTemp->setText("Temperatura en Córdoba: " + QString::number(temp) + " °C");
    } else {
        ui->labelTemp->setText("Error al cargar la temperatura");
    }

    reply->deleteLater(); // Limpiamos memoria
}