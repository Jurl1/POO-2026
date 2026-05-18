#include "pajaro.h"
#include <QPainter>
#include <cstdlib>

Pajaro::Pajaro(QWidget *parent) : QWidget(parent), velocidad(7) {
    int alturas[] = {150, 200, 240};
    int yRandom = alturas[rand() % 3];

    this->setGeometry(800, yRandom, 35, 25);

    timerPropio = new QTimer(this);
    connect(timerPropio, SIGNAL(timeout()), this, SLOT(slot_mover()));
    timerPropio->start(30);
    this->show();
}

void Pajaro::slot_mover() {
    this->move(this->x() - velocidad, this->y());
    if(this->x() < -50) this->deleteLater();
}

void Pajaro::aumentarVelocidad() {
    velocidad += 2;
}

void Pajaro::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::blue);
}