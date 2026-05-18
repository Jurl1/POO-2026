#ifndef TREX_H
#define TREX_H

#include <QWidget>

class TRex : public QWidget {
    Q_OBJECT
public:
    explicit TRex(QWidget *parent = nullptr);

    void saltar();
    void agacharse();
    void normal();
    void avanzar();
    void frenar();
    void procesarFisicas();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int velocidadY;
    bool isAgachado;
    const int PISO = 250;
};

#endif // TREX_H