#ifndef BATERIA_H
#define BATERIA_H

#include "instrumento.h"

class Bateria : public Instrumento  {

private:
    int tambores;

public:
    Bateria( int tambores = 5, QString marca = "Yamaha" );

    void sonar();

    int getTambores() const;
    void setTambores( int tambores );
};

#endif // BATERIA_H
