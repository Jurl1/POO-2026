#ifndef DIBUJO_H
#define DIBUJO_H

#include <QString>
#include <QVector>
#include <QPoint>

class QPainter;

// Clase abstracta base para todos los tipos de dibujo.
// Define la interfaz que cada tipo concreto debe implementar.
class Dibujo  {

public:
    Dibujo( const QString & nombre = "", const QString & categoria = "" );
    virtual ~Dibujo();

    // Método virtual puro: cada tipo de dibujo define cómo se renderiza
    virtual void dibujar( QPainter * painter ) const = 0;

    // Método virtual: devuelve un texto descriptivo del dibujo
    virtual QString descripcion() const;

    // Gestión de trazos capturados con el mouse
    void agregarPunto( const QPoint & punto );
    void nuevoTrazo();
    void finalizarTrazo();
    void limpiar();
    bool estaVacio() const;

    // Getters y setters
    QString getNombre() const;
    void setNombre( const QString & nombre );
    QString getCategoria() const;
    void setCategoria( const QString & categoria );

    // Acceso a trazos (para copiar entre tipos de dibujo)
    QVector< QVector< QPoint > > getTrazos() const;
    void setTrazos( const QVector< QVector< QPoint > > & trazos );

protected:
    QString m_nombre;
    QString m_categoria;
    QVector< QVector< QPoint > > m_trazos;      // Trazos finalizados
    QVector< QPoint > m_trazoActual;             // Trazo en curso
};

#endif // DIBUJO_H
