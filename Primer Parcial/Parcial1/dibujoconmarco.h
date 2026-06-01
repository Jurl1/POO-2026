#ifndef DIBUJOCONMARCO_H
#define DIBUJOCONMARCO_H

#include "dibujo.h"

// Dibujo a mano alzada con un marco decorativo alrededor
class DibujoConMarco : public Dibujo  {

public:
    DibujoConMarco( const QString & nombre = "", const QString & categoria = "" );

    void dibujar( QPainter * painter ) const override;
    QString descripcion() const override;
};

#endif // DIBUJOCONMARCO_H
