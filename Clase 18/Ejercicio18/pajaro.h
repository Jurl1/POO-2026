#ifndef PAJARO_H
#define PAJARO_H

#include <QWidget>
#include <QTimer>

class Pajaro : public QWidget {
    Q_OBJECT
public:
    explicit Pajaro(QWidget *parent = nullptr);
    void aumentarVelocidad();

private slots:
    void slot_mover();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *timerPropio;
    int velocidad;
};

#endif // PAJARO_H