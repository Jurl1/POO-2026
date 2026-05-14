#include "boton.h"
#include "ui_boton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QLinearGradient>

Boton::Boton(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Boton)
    , colorActual(Azul)
    , m_texto("")
{
    ui->setupUi(this);
    setCursor(Qt::PointingHandCursor);
}

Boton::~Boton()
{
    delete ui;
}

void Boton::colorear(Color c)
{
    colorActual = c;
    repaint();
}

void Boton::setTexto(const QString &texto)
{
    m_texto = texto;
    repaint();
}

void Boton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    // Color base segun la enumeracion
    QColor colorBase;
    QColor colorClaro;
    switch (colorActual) {
    case Azul:
        colorBase = QColor(30, 90, 200);
        colorClaro = QColor(60, 140, 255);
        break;
    case Verde:
        colorBase = QColor(30, 160, 80);
        colorClaro = QColor(60, 220, 120);
        break;
    case Magenta:
        colorBase = QColor(180, 30, 160);
        colorClaro = QColor(240, 60, 220);
        break;
    }

    // Gradiente horizontal de izquierda a derecha (similar a la imagen de referencia)
    QLinearGradient grad(0, 0, width(), 0);
    grad.setColorAt(0.0, colorClaro);
    grad.setColorAt(1.0, colorBase);

    painter.fillRect(rect(), grad);

    // Linea separadora inferior fina
    painter.setPen(QPen(colorBase.darker(150), 1));
    painter.drawLine(0, height() - 1, width(), height() - 1);

    // Texto blanco con sombra suave
    if (!m_texto.isEmpty()) {
        QFont font("Segoe UI", 13);
        font.setItalic(true);
        painter.setFont(font);

        // Sombra
        painter.setPen(QColor(0, 0, 0, 80));
        painter.drawText(rect().adjusted(22, 2, 2, 2), Qt::AlignVCenter | Qt::AlignLeft, m_texto);

        // Texto principal
        painter.setPen(Qt::white);
        painter.drawText(rect().adjusted(20, 0, 0, 0), Qt::AlignVCenter | Qt::AlignLeft, m_texto);
    }
}

void Boton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit signal_clic();
    }
}
