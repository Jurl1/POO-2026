#ifndef CAJAMEDICAMENTO_H
#define CAJAMEDICAMENTO_H

#include <QString>

class CajaMedicamento  {

private:
    int id;
    float dosisTotales;

public:
    CajaMedicamento( float dosis );
    CajaMedicamento( int id, float dosis );

    int getId() const;
    float getDosisTotales() const;

    CajaMedicamento operator+( const CajaMedicamento & otra ) const;
    bool operator==( const CajaMedicamento & otra ) const;

    QString toString() const;
};

#endif // CAJAMEDICAMENTO_H
