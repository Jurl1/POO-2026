#include "trex.h"
#include <QPainter>

TRex::TRex(QWidget *parent) : QWidget(parent), velocidadY(0), isAgachado(false) {
    this->setGeometry(50, PISO, 40, 50);
}

void TRex::saltar() {
    if (this->y() >= PISO) velocidadY = -15;
}

void TRex::agacharse() {
    if (!isAgachado && this->y() >= PISO) {
        isAgachado = true;
        this->setGeometry(this->x(), PISO + 25, 50, 25);
    }
}

void TRex::normal() {
    if (isAgachado) {
        isAgachado = false;
        this->setGeometry(this->x(), PISO, 40, 50);
    }
}

void TRex::avanzar() {
    if(this->x() < 400) this->move(this->x() + 5, this->y()); // Cambiado de 15 a 5
}

void TRex::frenar() {
    if(this->x() > 0) this->move(this->x() - 5, this->y()); // Cambiado de 15 a 5
}

void TRex::procesarFisicas() {
    int nuevaY = this->y() + velocidadY;

    if (nuevaY < PISO && !isAgachado) {
        velocidadY += 1; // Gravedad natural
    } else if (!isAgachado) {
        nuevaY = PISO;
        velocidadY = 0;
    }

    this->move(this->x(), nuevaY);
}

void TRex::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::darkGray);
}