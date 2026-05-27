#ifndef IMAGENNORMAL_H
#define IMAGENNORMAL_H

#include "imagenconetiqueta.h"

class ImagenNormal : public ImagenConEtiqueta  {
    Q_OBJECT

public:
    ImagenNormal( const QString & ruta,
                  const QString & etiqueta,
                  QWidget * parent = nullptr );

    void mostrar() override;

protected:
    void paintEvent( QPaintEvent * event ) override;
};

#endif // IMAGENNORMAL_H
