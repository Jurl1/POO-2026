#include "guitarra.h"
#include <QDebug>

Guitarra::Guitarra( int cuerdas, QString marca ) : Instrumento( marca ), cuerdas( cuerdas )  {
}

void Guitarra::sonar()  {
    qDebug() << "Guitarra suena...";
}

int Guitarra::getCuerdas() const  {
    return cuerdas;
}

void Guitarra::setCuerdas( int cuerdas )  {
    this->cuerdas = cuerdas;
}
