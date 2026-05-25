#include "electrico.h"
#include <QDebug>

Electrico::Electrico( int voltaje ) : voltaje( voltaje )  {
}

Electrico::~Electrico()  {
    qDebug() << "Desenchufado";
}

int Electrico::getVoltaje() const  {
    return voltaje;
}

void Electrico::setVoltaje( int voltaje )  {
    this->voltaje = voltaje;
}
