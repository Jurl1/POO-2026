#ifndef ELECTRICO_H
#define ELECTRICO_H

class Electrico  {

protected:
    int voltaje;

public:
    Electrico( int voltaje = 220 );
    ~Electrico();

    int getVoltaje() const;
    void setVoltaje( int voltaje );
};

#endif // ELECTRICO_H
