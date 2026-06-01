#include "dibujo.h"

Dibujo::Dibujo( const QString & nombre, const QString & categoria )
    : m_nombre( nombre ), m_categoria( categoria )  {
}

Dibujo::~Dibujo()  {
}

QString Dibujo::descripcion() const  {
    return m_nombre + " [" + m_categoria + "]";
}

void Dibujo::agregarPunto( const QPoint & punto )  {
    m_trazoActual.append( punto );
}

void Dibujo::nuevoTrazo()  {
    m_trazoActual.clear();
}

void Dibujo::finalizarTrazo()  {
    if ( ! m_trazoActual.isEmpty() )  {
        m_trazos.append( m_trazoActual );
        m_trazoActual.clear();
    }
}

void Dibujo::limpiar()  {
    m_trazos.clear();
    m_trazoActual.clear();
}

bool Dibujo::estaVacio() const  {
    return m_trazos.isEmpty() && m_trazoActual.isEmpty();
}

QString Dibujo::getNombre() const  {  return m_nombre;  }
void Dibujo::setNombre( const QString & nombre )  {  m_nombre = nombre;  }

QString Dibujo::getCategoria() const  {  return m_categoria;  }
void Dibujo::setCategoria( const QString & categoria )  {  m_categoria = categoria;  }

QVector< QVector< QPoint > > Dibujo::getTrazos() const  {  return m_trazos;  }
void Dibujo::setTrazos( const QVector< QVector< QPoint > > & trazos )  {  m_trazos = trazos;  }
