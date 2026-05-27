#include "imagen.h"
#include <QPainter>
#include <QPen>

Imagen::Imagen( QWidget * parent ) : QWidget( parent )  {
}

void Imagen::paintEvent( QPaintEvent * event )  {
    Q_UNUSED( event )

    QPainter painter( this );
    painter.setRenderHint( QPainter::SmoothPixmapTransform );

    if ( m_imagen.isNull() )  {
        // Placeholder cuando no hay imagen cargada
        painter.fillRect( rect(), QColor( 220, 220, 220 ) );
        painter.setPen( QColor( 150, 150, 150 ) );
        painter.setFont( QFont( "Arial", 11 ) );
        painter.drawText( rect(), Qt::AlignCenter, "Avatar" );
    }
    else  {
        QImage escalada = m_imagen.scaled( size(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation );
        int x = ( width()  - escalada.width()  ) / 2;
        int y = ( height() - escalada.height() ) / 2;
        painter.drawImage( x, y, escalada );

        // Borde sutil
        painter.setPen( QPen( QColor( 180, 180, 180 ), 1 ) );
        painter.drawRect( rect().adjusted( 0, 0, -1, -1 ) );
    }
}

void Imagen::setImagen( const QImage & imagen )  {
    m_imagen = imagen;
    update();
}
