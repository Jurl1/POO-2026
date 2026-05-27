#include "imagennormal.h"
#include <QPainter>
#include <QFont>

ImagenNormal::ImagenNormal( const QString & ruta,
                             const QString & etiqueta,
                             QWidget * parent )
    : ImagenConEtiqueta( ruta, etiqueta, parent )  {
}

void ImagenNormal::mostrar()  {
    update();
}

void ImagenNormal::paintEvent( QPaintEvent * event )  {
    Q_UNUSED( event )

    QPainter painter( this );
    painter.setRenderHint( QPainter::SmoothPixmapTransform );

    if ( m_imagen.isNull() )  {
        painter.fillRect( rect(), QColor( 240, 240, 240 ) );
        painter.setPen( QColor( 150, 150, 150 ) );
        painter.drawText( rect(), Qt::AlignCenter, "Sin imagen" );
        return;
    }

    // Área para la imagen (dejamos espacio abajo para la etiqueta)
    int margenEtiqueta = 25;
    QRect areaImagen( 0, 0, width(), height() - margenEtiqueta );

    QImage escalada = m_imagen.scaled( areaImagen.size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation );

    int x = areaImagen.x() + ( areaImagen.width()  - escalada.width()  ) / 2;
    int y = areaImagen.y() + ( areaImagen.height() - escalada.height() ) / 2;

    painter.drawImage( x, y, escalada );

    // Dibujar la etiqueta debajo
    painter.setPen( QColor( 60, 60, 60 ) );
    painter.setFont( QFont( "Arial", 9 ) );
    QRect areaEtiqueta( 0, height() - margenEtiqueta, width(), margenEtiqueta );
    painter.drawText( areaEtiqueta, Qt::AlignCenter, m_etiqueta );
}
