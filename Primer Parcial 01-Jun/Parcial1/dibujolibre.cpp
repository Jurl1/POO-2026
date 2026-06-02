#include "dibujolibre.h"
#include <QPainter>
#include <QPen>

DibujoLibre::DibujoLibre( const QString & nombre, const QString & categoria )
    : Dibujo( nombre, categoria )  {
}

// Dibuja los trazos directamente sin decoraciones
void DibujoLibre::dibujar( QPainter * painter ) const  {
    QPen pen( Qt::black, 2 );
    painter->setPen( pen );
    painter->setRenderHint( QPainter::Antialiasing );

    // Dibujar trazos finalizados
    for ( int i = 0; i < m_trazos.size(); i++ )  {
        const QVector< QPoint > & trazo = m_trazos.at( i );
        for ( int j = 1; j < trazo.size(); j++ )  {
            painter->drawLine( trazo.at( j - 1 ), trazo.at( j ) );
        }
    }

    // Dibujar el trazo en curso
    for ( int j = 1; j < m_trazoActual.size(); j++ )  {
        painter->drawLine( m_trazoActual.at( j - 1 ), m_trazoActual.at( j ) );
    }
}

QString DibujoLibre::descripcion() const  {
    return "Dibujo libre: " + m_nombre + " [" + m_categoria + "]";
}
