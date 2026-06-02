#ifndef LIENZO_H
#define LIENZO_H

#include <QWidget>
#include <QMouseEvent>
#include <QImage>

class Dibujo;

// Widget personalizado de dibujo. Captura eventos de mouse y delega
// el renderizado al objeto Dibujo asignado (polimorfismo).
// Debe estar promocionado en Qt Designer.
class Lienzo : public QWidget  {
    Q_OBJECT

public:
    Lienzo( QWidget * parent = nullptr );
    ~Lienzo();

    // Asigna el dibujo actual (puntero a la clase base)
    void setDibujo( Dibujo * dibujo );
    Dibujo * getDibujo() const;

    // Exporta el contenido del lienzo como QImage
    QImage exportarImagen();

    // Limpia todos los trazos
    void limpiarLienzo();

protected:
    void paintEvent( QPaintEvent * event ) override;
    void mousePressEvent( QMouseEvent * event ) override;
    void mouseMoveEvent( QMouseEvent * event ) override;
    void mouseReleaseEvent( QMouseEvent * event ) override;

signals:
    void signal_dibujoModificado();

private:
    Dibujo * m_dibujo;
    bool m_dibujando;
};

#endif // LIENZO_H
