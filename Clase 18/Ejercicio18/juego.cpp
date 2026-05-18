#include "juego.h"
#include "pajaro.h"
#include <QPainter>
#include <cstdlib>

Juego::Juego(QWidget *parent) : QWidget(parent), gameOver(false), velocidadCactus(5),
    moviendoDerecha(false), moviendoIzquierda(false) {
    this->setFixedSize(800, 350);
    this->setFocusPolicy(Qt::StrongFocus);

    dino = new TRex(this);

    lblGameOver = new QLabel("GAME OVER\nPresiona 'R' para reiniciar", this);
    lblGameOver->setGeometry(300, 100, 200, 50);
    lblGameOver->setAlignment(Qt::AlignCenter);
    lblGameOver->setStyleSheet("font-size: 16px; font-weight: bold; color: red;");
    lblGameOver->hide();

    // 1. Timer principal a 30ms
    mainTimer = new QTimer(this);
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(slot_mainTimer()));
    mainTimer->start(30);

    // 2. Timer de Pájaros (Cada 5s)
    spawnerTimer = new QTimer(this);
    connect(spawnerTimer, SIGNAL(timeout()), this, SLOT(slot_spawnPajaro()));
    spawnerTimer->start(5000);

    // 3. Timer de Dificultad (Sube velocidad cada 10s)
    dificultadTimer = new QTimer(this);
    connect(dificultadTimer, SIGNAL(timeout()), this, SLOT(slot_aumentarDificultad()));
    dificultadTimer->start(10000);

    QTimer::singleShot(1500, this, SLOT(slot_spawnCactus()));
}

void Juego::slot_mainTimer() {
    if(gameOver) return;

    dino->procesarFisicas();

    // NUEVO: Movimiento fluido leyendo los booleanos
    if (moviendoDerecha) dino->avanzar();
    if (moviendoIzquierda) dino->frenar();

    // Mover Cactus y detectar colisión
    for (int i = 0; i < cactusList.size(); ++i) {
        QWidget *c = cactusList[i];
        c->move(c->x() - velocidadCactus, c->y());

        if (dino->geometry().intersects(c->geometry())) gameOver = true;

        if (c->x() < -50) {
            c->deleteLater();
            cactusList.removeAt(i);
            i--;
        }
    }

    // Colisión con Pájaros
    QList<Pajaro*> pajaros = this->findChildren<Pajaro*>();
    for(Pajaro* p : pajaros) {
        if (dino->geometry().intersects(p->geometry())) gameOver = true;
    }

    if(gameOver) lblGameOver->show();
}

void Juego::slot_spawnPajaro() {
    if(!gameOver) new Pajaro(this);
}

void Juego::slot_spawnCactus() {
    if(!gameOver) {
        QWidget *cactus = new QWidget(this);
        cactus->setGeometry(800, 270, 20, 30);
        cactus->setStyleSheet("background-color: green;");
        cactus->show();
        cactusList.append(cactus);
    }

    // El próximo cactus sale en un tiempo aleatorio usando singleShot
    if(!gameOver) {
        int tiempoRandom = 1000 + (rand() % 2000);
        QTimer::singleShot(tiempoRandom, this, SLOT(slot_spawnCactus()));
    }
}

void Juego::slot_aumentarDificultad() {
    if(!gameOver) {
        velocidadCactus += 1;
        QList<Pajaro*> pajaros = this->findChildren<Pajaro*>();
        for(Pajaro* p : pajaros) p->aumentarVelocidad();
    }
}

void Juego::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return; // Ignora el tartamudeo de Windows

    if (gameOver && event->key() == Qt::Key_R) {
        reiniciarJuego();
        return;
    }

    if(!gameOver) {
        if (event->key() == Qt::Key_Space) dino->saltar();
        if (event->key() == Qt::Key_Down) dino->agacharse();

        // En lugar de moverlo de golpe, encendemos el "motor"
        if (event->key() == Qt::Key_Right) moviendoDerecha = true;
        if (event->key() == Qt::Key_Left) moviendoIzquierda = true;
    }
}

void Juego::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return; // Ignora el tartamudeo de Windows

    if (event->key() == Qt::Key_Down && !gameOver) dino->normal();

    // Apagamos el "motor" cuando soltás la tecla
    if (event->key() == Qt::Key_Right) moviendoDerecha = false;
    if (event->key() == Qt::Key_Left) moviendoIzquierda = false;
}

void Juego::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::white);
    painter.drawLine(0, 300, 800, 300); // Línea del piso
}

void Juego::reiniciarJuego() {
    gameOver = false;
    lblGameOver->hide();
    velocidadCactus = 5;
    moviendoDerecha = false;
    moviendoIzquierda = false;

    for(QWidget* c : cactusList) c->deleteLater();
    cactusList.clear();

    QList<Pajaro*> pajaros = this->findChildren<Pajaro*>();
    for(Pajaro* p : pajaros) p->deleteLater();

    dino->setGeometry(50, 250, 40, 50);
    QTimer::singleShot(1000, this, SLOT(slot_spawnCactus()));
}