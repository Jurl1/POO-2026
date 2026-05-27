#include "imagenconmarco.h"
#include <QPainter>
#include <QPen>
#include <QFont>

ImagenConMarco::ImagenConMarco( const QString & ruta,
                                 const QString & etiqueta,
                                 QWidget * parent )
    : ImagenConEtiqueta( ruta, etiqueta, parent )  {
}

void ImagenConMarco::mostrar()  {
    update();
}

void ImagenConMarco::paintEvent( QPaintEvent * event )  {
    Q_UNUSED( event )

    QPainter painter( this );
    painter.setRenderHint( QPainter::SmoothPixmapTransform );
    painter.setRenderHint( QPainter::Antialiasing );

    int marcoAncho = 8;
    int margenEtiqueta = 28;

    // Fondo del marco
    painter.fillRect( rect(), QColor( 40, 40, 80 ) );

    // Borde exterior del marco
    QPen penMarco( QColor( 100, 130, 220 ), 3 );
    painter.setPen( penMarco );
    painter.drawRect( rect().adjusted( 1, 1, -2, -2 ) );

    if ( m_imagen.isNull() )  {
        painter.setPen( QColor( 200, 200, 200 ) );
        painter.drawText( rect(), Qt::AlignCenter, "Sin imagen" );
        return;
    }

    // Área interna para la imagen (dentro del marco y dejando espacio para la etiqueta)
    QRect areaImagen( marcoAncho, marcoAncho,
                      width() - marcoAncho * 2,
                      height() - marcoAncho * 2 - margenEtiqueta );

    QImage escalada = m_imagen.scaled( areaImagen.size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation );

    int x = areaImagen.x() + ( areaImagen.width()  - escalada.width()  ) / 2;
    int y = areaImagen.y() + ( areaImagen.height() - escalada.height() ) / 2;

    painter.drawImage( x, y, escalada );

    // Borde interno alrededor de la imagen
    QPen penInterno( QColor( 180, 190, 240 ), 1 );
    painter.setPen( penInterno );
    painter.drawRect( areaImagen );

    // Etiqueta dentro del marco
    painter.setPen( QColor( 220, 220, 255 ) );
    painter.setFont( QFont( "Arial", 9, QFont::Bold ) );
    QRect areaEtiqueta( marcoAncho, height() - marcoAncho - margenEtiqueta,
                        width() - marcoAncho * 2, margenEtiqueta );
    painter.drawText( areaEtiqueta, Qt::AlignCenter, m_etiqueta );
}
