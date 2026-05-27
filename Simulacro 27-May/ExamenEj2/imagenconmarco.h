#ifndef IMAGENCONMARCO_H
#define IMAGENCONMARCO_H

#include "imagenconetiqueta.h"

class ImagenConMarco : public ImagenConEtiqueta  {
    Q_OBJECT

public:
    ImagenConMarco( const QString & ruta,
                    const QString & etiqueta,
                    QWidget * parent = nullptr );

    void mostrar() override;

protected:
    void paintEvent( QPaintEvent * event ) override;
};

#endif // IMAGENCONMARCO_H
