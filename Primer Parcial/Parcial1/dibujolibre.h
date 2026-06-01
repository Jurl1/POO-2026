#ifndef DIBUJOLIBRE_H
#define DIBUJOLIBRE_H

#include "dibujo.h"

// Dibujo a mano alzada sin decoraciones adicionales
class DibujoLibre : public Dibujo  {

public:
    DibujoLibre( const QString & nombre = "", const QString & categoria = "" );

    void dibujar( QPainter * painter ) const override;
    QString descripcion() const override;
};

#endif // DIBUJOLIBRE_H
