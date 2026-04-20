#include "login.h"
#include <QGridLayout>
#include <QPainter>
#include <QNetworkRequest>
#include <QUrl>
#include <QMessageBox>

Login::Login(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Sistema de Ingreso");
    resize(400, 300);

    // 1. Descargamos el fondo del Login
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(on_descargaFondoFinalizada(QNetworkReply*)));

    QNetworkRequest request((QUrl("https://www.w3schools.com/w3images/mountains.jpg")));
    manager->get(request);

    // 2. Elementos visuales
    leUsuario = new QLineEdit();
    leUsuario->setPlaceholderText("Usuario (admin)");

    leClave = new QLineEdit();
    leClave->setPlaceholderText("Clave (1234)");
    leClave->setEchoMode(QLineEdit::Password);

    btnIngresar = new QPushButton("Ingresar");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(leUsuario, 0, 0);
    layout->addWidget(leClave, 1, 0);
    layout->addWidget(btnIngresar, 2, 0);
    layout->setContentsMargins(100, 100, 100, 100); // Márgenes para que no ocupe todo

    // 3. Preparamos la segunda ventana oculta
    ventanaSecundaria = new Ventana();

    // Conectamos la señal que emite la ventana secundaria al terminar, con el slot para abrirla
    connect(ventanaSecundaria, SIGNAL(descargaCompletada()), this, SLOT(abrirVentanaSecundaria()));
    connect(btnIngresar, SIGNAL(clicked()), this, SLOT(on_btnIngresar_clicked()));
}

void Login::on_descargaFondoFinalizada(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        imagenFondo = QImage::fromData(reply->readAll());
        update(); // Le decimos a Qt que redibuje la ventana para que se vea el fondo
    }
    reply->deleteLater();
}

void Login::paintEvent(QPaintEvent *) {
    // Dibujamos la imagen de fondo del Login si ya se descargó
    if (!imagenFondo.isNull()) {
        QPainter painter(this);
        QPixmap pixmap = QPixmap::fromImage(imagenFondo).scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, pixmap);
    }
}

void Login::on_btnIngresar_clicked() {
    if (leUsuario->text() == "admin" && leClave->text() == "1234") {

        // Bloqueamos el botón y avisamos al usuario para que espere la descarga
        btnIngresar->setText("Descargando imagen, espere...");
        btnIngresar->setEnabled(false);

        // Le ordenamos a la ventana secundaria que busque su imagen (NO la mostramos aún)
        ventanaSecundaria->iniciarDescarga("https://www.w3schools.com/w3images/nature.jpg");

    } else {
        QMessageBox::warning(this, "Error", "Usuario o clave incorrectos");
        leClave->clear();
    }
}

void Login::abrirVentanaSecundaria() {
    // Este slot solo se dispara cuando la ventana secundaria grita "¡Ya tengo la imagen!"
    ventanaSecundaria->showFullScreen();
    this->close();
}