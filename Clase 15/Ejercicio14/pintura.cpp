#include "pintura.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

Pintura::Pintura(QWidget *parent) : QWidget(parent), dibujando(false), colorPincel(Qt::black), grosorPincel(5) {
    setFocusPolicy(Qt::StrongFocus); // Fundamental para que el QWidget escuche el teclado (Escape, R, G, B)
}

void Pintura::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dibujar los trazos viejos
    for (const Trazo &trazo : std::as_const(trazos)) {
        if (trazo.puntos.size() > 1) {
            QPen pen(trazo.color, trazo.grosor, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            painter.setPen(pen);
            for (int i = 0; i < trazo.puntos.size() - 1; ++i) {
                painter.drawLine(trazo.puntos[i], trazo.puntos[i+1]);
            }
        }
    }

    // Dibujar el trazo actual en vivo
    if (trazoActual.puntos.size() > 1) {
        QPen pen(colorPincel, grosorPincel, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        for (int i = 0; i < trazoActual.puntos.size() - 1; ++i) {
            painter.drawLine(trazoActual.puntos[i], trazoActual.puntos[i+1]);
        }
    }
}

void Pintura::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dibujando = true;
        trazoActual.puntos.clear();
        trazoActual.color = colorPincel;
        trazoActual.grosor = grosorPincel;
        trazoActual.puntos.append(event->pos());
    }
}

void Pintura::mouseMoveEvent(QMouseEvent *event) {
    if (dibujando && (event->buttons() & Qt::LeftButton)) {
        trazoActual.puntos.append(event->pos());
        update(); // Llama a paintEvent
    }
}

void Pintura::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && dibujando) {
        dibujando = false;
        if (!trazoActual.puntos.isEmpty()) {
            trazos.append(trazoActual);
        }
        trazoActual.puntos.clear();
        update();
    }
}

void Pintura::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        grosorPincel++;
    } else if (event->angleDelta().y() < 0 && grosorPincel > 1) {
        grosorPincel--;
    }
}

void Pintura::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_R) colorPincel = Qt::red;
    else if (event->key() == Qt::Key_G) colorPincel = Qt::green;
    else if (event->key() == Qt::Key_B) colorPincel = Qt::blue;
    else if (event->key() == Qt::Key_Escape) {
        trazos.clear();
        trazoActual.puntos.clear();
        update();
    }
}