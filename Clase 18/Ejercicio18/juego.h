#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include "trex.h"

class Juego : public QWidget {
    Q_OBJECT
public:
    explicit Juego(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_mainTimer();
    void slot_spawnPajaro();
    void slot_spawnCactus();
    void slot_aumentarDificultad();

private:
    TRex *dino;
    QTimer *mainTimer;
    QTimer *spawnerTimer;
    QTimer *dificultadTimer;

    QList<QWidget*> cactusList;

    bool gameOver;
    bool moviendoDerecha;
    bool moviendoIzquierda;
    int velocidadCactus;
    QLabel *lblGameOver;

    void reiniciarJuego();
};

#endif // JUEGO_H