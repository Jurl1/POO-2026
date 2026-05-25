#ifndef TECLADO_H
#define TECLADO_H

#include "instrumento.h"
#include "electrico.h"

class Teclado : public Instrumento, public Electrico  {

private:
    int teclas;

public:
    Teclado( int teclas = 61, QString marca = "Yamaha", int voltaje = 220 );

    void sonar();

    int getTeclas() const;
    void setTeclas( int teclas );
};

#endif // TECLADO_H
