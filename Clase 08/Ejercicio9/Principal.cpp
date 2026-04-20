#include "Principal.h"
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QNetworkRequest>
#include <QUrl>

Principal::Principal(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Descargador de Imágenes");
    resize(400, 300);

    // Instanciamos el manager que maneja la red
    manager = new QNetworkAccessManager(this);

    // Interfaz gráfica
    // Ponemos una imagen de prueba por defecto (puede ser cualquiera)
    leUrl = new QLineEdit("https://fs.ubp.edu.ar/adfs/portal/logo/logo.png?id=856C9273B29CBFD5FAE87C8430CAFA167A97EE35A82C3A3FC436031F78090952");
    pbDescargar = new QPushButton("Descargar");
    lImagen = new QLabel("La imagen aparecerá aquí...");
    lImagen->setAlignment(Qt::AlignCenter);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(leUrl);
    layout->addWidget(pbDescargar);
    layout->addWidget(lImagen);

    // Conexiones (Signals y Slots)
    // 1. Cuando se hace clic en el botón, llamamos a descargar
    connect(pbDescargar, SIGNAL(clicked()), this, SLOT(slot_descargar()));

    // 2. Cuando el manager termina de descargar, llama al slot finalizada
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));
}

void Principal::slot_descargar() {
    // Leemos la URL del QLineEdit
    QNetworkRequest request;
    request.setUrl(QUrl(leUrl->text()));

    // Seteamos el User-Agent como recomienda la teoría de la clase
    request.setRawHeader("User-Agent", "MiNavegador 1.0");

    // Ejecutamos la petición GET
    manager->get(request);

    lImagen->setText("Descargando...");
}

void Principal::slot_descargaFinalizada(QNetworkReply *reply) {
    // Verificamos que no hubo error (ej. error 404, sin internet, etc.)
    if (reply->error() == QNetworkReply::NoError) {

        // Leemos todos los bytes que trajo la respuesta
        QByteArray data = reply->readAll();

        // Convertimos esos bytes a una QImage
        QImage image = QImage::fromData(data);

        // La mostramos en el QLabel (escalada para que no deforme la ventana)
        lImagen->setPixmap(QPixmap::fromImage(image).scaled(380, 250, Qt::KeepAspectRatio));

    } else {
        lImagen->setText("Error al descargar la imagen.");
    }

    // Liberar memoria del reply
    reply->deleteLater();
}