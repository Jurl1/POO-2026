#ifndef INSTRUMENTO_H
#define INSTRUMENTO_H

#include <QString>

class Instrumento  {

protected:
    QString marca;

public:
    Instrumento( QString marca = "Yamaha" );
    virtual ~Instrumento();

    virtual void sonar() = 0;
    virtual void verlo();

    QString getMarca() const;
    void setMarca( QString marca );
};

#endif // INSTRUMENTO_H
