#ifndef PINTURA_H
#define PINTURA_H

#include <QWidget>
#include <QPoint>
#include <QColor>
#include <QVector>

// Estructura para guardar cada línea que dibujamos
struct Trazo {
    QVector<QPoint> puntos;
    QColor color;
    int grosor;
};

class Pintura : public QWidget {
    Q_OBJECT
public:
    explicit Pintura(QWidget *parent = nullptr);

protected:
    // Los eventos que pide el ejercicio
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QVector<Trazo> trazos;
    Trazo trazoActual;
    bool dibujando;
    QColor colorPincel;
    int grosorPincel;
};

#endif // PINTURA_H