#include "dibujoconmarco.h"
#include <QPainter>
#include <QPen>

DibujoConMarco::DibujoConMarco( const QString & nombre, const QString & categoria )
    : Dibujo( nombre, categoria )  {
}

// Dibuja un marco decorativo y luego los trazos dentro de él
void DibujoConMarco::dibujar( QPainter * painter ) const  {
    painter->setRenderHint( QPainter::Antialiasing );

    int ancho = painter->device()->width();
    int alto  = painter->device()->height();

    // Marco exterior
    int margen = 12;
    QRect marcoExt( margen, margen, ancho - margen * 2, alto - margen * 2 );

    QPen penMarco( QColor( 50, 50, 110 ), 3 );
    painter->setPen( penMarco );
    painter->drawRect( marcoExt );

    // Marco interior decorativo (línea punteada)
    QPen penInterno( QColor( 110, 120, 200 ), 1, Qt::DashLine );
    painter->setPen( penInterno );
    painter->drawRect( marcoExt.adjusted( 6, 6, -6, -6 ) );

    // Esquinas decorativas
    int esquina = 15;
    QPen penEsquina( QColor( 80, 80, 180 ), 2 );
    painter->setPen( penEsquina );

    // Superior izquierda
    painter->drawLine( margen, margen + esquina, margen, margen );
    painter->drawLine( margen, margen, margen + esquina, margen );
    // Superior derecha
    painter->drawLine( ancho - margen - esquina, margen, ancho - margen, margen );
    painter->drawLine( ancho - margen, margen, ancho - margen, margen + esquina );
    // Inferior izquierda
    painter->drawLine( margen, alto - margen - esquina, margen, alto - margen );
    painter->drawLine( margen, alto - margen, margen + esquina, alto - margen );
    // Inferior derecha
    painter->drawLine( ancho - margen - esquina, alto - margen, ancho - margen, alto - margen );
    painter->drawLine( ancho - margen, alto - margen - esquina, ancho - margen, alto - margen );

    // Dibujar trazos finalizados
    QPen penDibujo( Qt::black, 2 );
    painter->setPen( penDibujo );

    for ( int i = 0; i < m_trazos.size(); i++ )  {
        const QVector< QPoint > & trazo = m_trazos.at( i );
        for ( int j = 1; j < trazo.size(); j++ )  {
            painter->drawLine( trazo.at( j - 1 ), trazo.at( j ) );
        }
    }

    // Dibujar trazo en curso
    for ( int j = 1; j < m_trazoActual.size(); j++ )  {
        painter->drawLine( m_trazoActual.at( j - 1 ), m_trazoActual.at( j ) );
    }
}

QString DibujoConMarco::descripcion() const  {
    return "Dibujo con marco: " + m_nombre + " [" + m_categoria + "]";
}
