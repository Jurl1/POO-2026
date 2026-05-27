#ifndef IMAGEN_H
#define IMAGEN_H

#include <QWidget>
#include <QImage>

class Imagen : public QWidget  {
    Q_OBJECT

public:
    Imagen( QWidget * parent = nullptr );

protected:
    void paintEvent( QPaintEvent * event ) override;

public slots:
    void setImagen( const QImage & imagen );

private:
    QImage m_imagen;
};

#endif // IMAGEN_H
