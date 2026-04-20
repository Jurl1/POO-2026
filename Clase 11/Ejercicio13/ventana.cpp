#include "ventana.h"
#include <QPainter>
#include <QNetworkRequest>
#include <QUrl>
#include <QMessageBox>

Ventana::Ventana(QWidget *parent) : QWidget(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_descargaFinalizada(QNetworkReply*)));
}

void Ventana::iniciarDescarga(const QString &url) {
    QNetworkRequest request((QUrl(url)));
    manager->get(request);
}

void Ventana::on_descargaFinalizada(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        imagenFondo = QImage::fromData(reply->readAll());

        // ¡Magia aquí! Emitimos la señal avisando que la descarga terminó
        emit descargaCompletada();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo descargar la imagen de la ventana secundaria.");
    }
    reply->deleteLater();
}

void Ventana::paintEvent(QPaintEvent *) {
    if (!imagenFondo.isNull()) {
        QPainter painter(this);

        // El ejercicio pide que no se deforme (KeepAspectRatio)
        QPixmap pixmap = QPixmap::fromImage(imagenFondo).scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Matemáticas simples para centrar la imagen en la pantalla
        int x = (this->width() - pixmap.width()) / 2;
        int y = (this->height() - pixmap.height()) / 2;

        // Pintamos un fondo negro para las franjas vacías y luego la imagen centrada
        painter.fillRect(this->rect(), Qt::black);
        painter.drawPixmap(x, y, pixmap);
    }
}