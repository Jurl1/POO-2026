#include "CaptchaWidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QRandomGenerator>

CaptchaWidget::CaptchaWidget(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Validación Captcha");
    resize(300, 200);

    regenerarCaptcha();

    // Controles inferiores
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch(); // Empuja los controles hacia abajo

    QHBoxLayout *controlsLayout = new QHBoxLayout();
    leIngreso = new QLineEdit();
    leIngreso->setPlaceholderText("Ingrese los numeros");

    QPushButton *btnValidar = new QPushButton("Validar");

    controlsLayout->addWidget(leIngreso);
    controlsLayout->addWidget(btnValidar);
    mainLayout->addLayout(controlsLayout);

    connect(btnValidar, SIGNAL(clicked()), this, SLOT(validarCaptcha()));
    connect(leIngreso, SIGNAL(returnPressed()), this, SLOT(validarCaptcha()));
}

void CaptchaWidget::regenerarCaptcha() {
    int randomInt = QRandomGenerator::global()->bounded(10000, 99999);
    numeroCaptcha = QString::number(randomInt);
    update(); // Obliga a redibujar el widget
}

void CaptchaWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Fondo
    painter.fillRect(10, 10, width() - 20, 100, Qt::lightGray);

    // Líneas de ruido
    painter.setPen(QPen(Qt::darkGray, 2));
    for (int i = 0; i < 15; ++i) {
        int x1 = QRandomGenerator::global()->bounded(10, width() - 10);
        int y1 = QRandomGenerator::global()->bounded(10, 110);
        int x2 = QRandomGenerator::global()->bounded(10, width() - 10);
        int y2 = QRandomGenerator::global()->bounded(10, 110);
        painter.drawLine(x1, y1, x2, y2);
    }

    // Texto del captcha
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(30);
    font.setBold(true);
    font.setItalic(true);
    painter.setFont(font);

    for (int i = 0; i < numeroCaptcha.length(); ++i) {
        int posX = 30 + (i * 40) + QRandomGenerator::global()->bounded(-5, 5);
        int posY = 70 + QRandomGenerator::global()->bounded(-10, 10);
        painter.drawText(posX, posY, QString(numeroCaptcha.at(i)));
    }
}

void CaptchaWidget::validarCaptcha() {
    if (leIngreso->text() == numeroCaptcha) {
        QMessageBox::information(this, "Éxito", "Captcha correcto.");
        close();
    } else {
        QMessageBox::warning(this, "Error", "Captcha incorrecto.");
        leIngreso->clear();
        regenerarCaptcha();
    }
}