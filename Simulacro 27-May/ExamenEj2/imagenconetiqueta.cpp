#include "imagenconetiqueta.h"

ImagenConEtiqueta::ImagenConEtiqueta( const QString & ruta,
                                      const QString & etiqueta,
                                      QWidget * parent )
    : QWidget( parent ), m_ruta( ruta ), m_etiqueta( etiqueta )  {

    m_imagen.load( ruta );
}

QString ImagenConEtiqueta::getRuta() const  {
    return m_ruta;
}

QString ImagenConEtiqueta::getEtiqueta() const  {
    return m_etiqueta;
}
