#ifndef SENSOR_H
#define SENSOR_H

#include <cstdlib>

class Sensor  {
private:
    int valorActual;

public:
    Sensor() : valorActual( rand() % 1024 )  {  }

    // inline implícito (definido dentro de la clase)
    int getValorBruto()  {  return valorActual;  }

    // offline (definido fuera, sin inline)
    int getValorBrutoOffline();

    // inline explícito (definido fuera con keyword inline)
    inline double getValorNormalizado()  {  return valorActual / 1023.0;  }

    // offline (definido fuera, sin inline)
    double getValorNormalizadoOffline();
};

// Definición offline — función normal, no inline
int Sensor::getValorBrutoOffline()  {
    return valorActual;
}

// Definición offline — función normal, no inline
double Sensor::getValorNormalizadoOffline()  {
    return valorActual / 1023.0;
}

#endif // SENSOR_H
