#include "lienzo.h"
#include "dibujo.h"
#include <QPainter>
#include <QDebug>

Lienzo::Lienzo( QWidget * parent )
    : QWidget( parent ), m_dibujo( nullptr ), m_dibujando( false )  {

    setMinimumSize( 400, 300 );
    setCursor( Qt::CrossCursor );
}

Lienzo::~Lienzo()  {
    // No libera m_dibujo: su ciclo de vida es responsabilidad de VentanaPrincipal
}

void Lienzo::setDibujo( Dibujo * dibujo )  {
    m_dibujo = dibujo;
    update();
}

Dibujo * Lienzo::getDibujo() const  {
    return m_dibujo;
}

// Renderiza el contenido delegando al objeto Dibujo (polimorfismo)
void Lienzo::paintEvent( QPaintEvent * event )  {
    Q_UNUSED( event )

    QPainter painter( this );
    painter.fillRect( rect(), Qt::white );

    if ( m_dibujo )  {
        m_dibujo->dibujar( & painter );
    }
}

// Inicia un nuevo trazo al presionar el botón izquierdo
void Lienzo::mousePressEvent( QMouseEvent * event )  {
    if ( event->button() == Qt::LeftButton && m_dibujo )  {
        m_dibujando = true;
        m_dibujo->nuevoTrazo();
        m_dibujo->agregarPunto( event->pos() );
        update();
    }
}

// Agrega puntos al trazo mientras se mueve el mouse con botón presionado
void Lienzo::mouseMoveEvent( QMouseEvent * event )  {
    if ( m_dibujando && m_dibujo )  {
        m_dibujo->agregarPunto( event->pos() );
        update();
        emit signal_dibujoModificado();
    }
}

// Finaliza el trazo al soltar el botón
void Lienzo::mouseReleaseEvent( QMouseEvent * event )  {
    if ( event->button() == Qt::LeftButton && m_dibujando && m_dibujo )  {
        m_dibujando = false;
        m_dibujo->finalizarTrazo();
        update();
        emit signal_dibujoModificado();
    }
}

// Genera una QImage con el contenido actual del lienzo
QImage Lienzo::exportarImagen()  {
    QImage imagen( size(), QImage::Format_ARGB32 );
    imagen.fill( Qt::white );

    QPainter painter( & imagen );
    if ( m_dibujo )  {
        m_dibujo->dibujar( & painter );
    }

    return imagen;
}

// Elimina todos los trazos del dibujo actual
void Lienzo::limpiarLienzo()  {
    if ( m_dibujo )  {
        m_dibujo->limpiar();
    }
    update();
    emit signal_dibujoModificado();
}
