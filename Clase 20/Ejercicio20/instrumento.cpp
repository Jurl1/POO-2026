#include "instrumento.h"
#include <QDebug>

Instrumento::Instrumento( QString marca ) : marca( marca )  {
}

Instrumento::~Instrumento()  {
}

void Instrumento::verlo()  {
    qDebug() << "Marca:" << this->marca;
}

QString Instrumento::getMarca() const  {
    return marca;
}

void Instrumento::setMarca( QString marca )  {
    this->marca = marca;
}
