#ifndef GUITARRA_H
#define GUITARRA_H

#include "instrumento.h"

class Guitarra : public Instrumento  {

private:
    int cuerdas;

public:
    Guitarra( int cuerdas = 6, QString marca = "Yamaha" );

    void sonar();

    int getCuerdas() const;
    void setCuerdas( int cuerdas );
};

#endif // GUITARRA_H
