#include "teclado.h"
#include <QDebug>

Teclado::Teclado( int teclas, QString marca, int voltaje )
    : Instrumento( marca ), Electrico( voltaje ), teclas( teclas )  {
}

void Teclado::sonar()  {
    qDebug() << "Teclado suena...";
}

int Teclado::getTeclas() const  {
    return teclas;
}

void Teclado::setTeclas( int teclas )  {
    this->teclas = teclas;
}
