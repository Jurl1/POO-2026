#include "bateria.h"
#include <QDebug>

Bateria::Bateria( int tambores, QString marca ) : Instrumento( marca ), tambores( tambores )  {
}

void Bateria::sonar()  {
    qDebug() << "Batería suena...";
}

int Bateria::getTambores() const  {
    return tambores;
}

void Bateria::setTambores( int tambores )  {
    this->tambores = tambores;
}
