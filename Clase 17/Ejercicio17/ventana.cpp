#include "ventana.h"
#include "ui_ventana.h"
#include "boton.h"
#include <QPainter>
#include <QLinearGradient>
#include <QMessageBox>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
{
    ui->setupUi(this);
    setWindowTitle("Ejercicio 17");
    setMinimumSize(400, 500);

    // Colorear cada boton con la enumeracion de Boton
    ui->Boton_1->colorear(Boton::Azul);
    ui->Boton_2->colorear(Boton::Verde);
    ui->Boton_3->colorear(Boton::Magenta);
    ui->Boton_4->colorear(Boton::Verde);
    ui->Boton_5->colorear(Boton::Azul);

    // Textos (similares a la imagen de referencia)
    ui->Boton_1->setTexto("Mi dentista");
    ui->Boton_2->setTexto("Visitas");
    ui->Boton_3->setTexto("Tecnicas de higiene");
    ui->Boton_4->setTexto("Mi boca");
    ui->Boton_5->setTexto("Hora de cepillarse");

    // Conectar la signal_clic de cada boton
    connect(ui->Boton_1, &Boton::signal_clic, this, &Ventana::onBotonClicado);
    connect(ui->Boton_2, &Boton::signal_clic, this, &Ventana::onBotonClicado);
    connect(ui->Boton_3, &Boton::signal_clic, this, &Ventana::onBotonClicado);
    connect(ui->Boton_4, &Boton::signal_clic, this, &Ventana::onBotonClicado);
    connect(ui->Boton_5, &Boton::signal_clic, this, &Ventana::onBotonClicado);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    // Construimos el fondo como QImage en codigo (cumple con drawImage de la consigna)
    // Igual al fondo de la imagen de referencia: gradiente diagonal multicolor
    QImage imagenFondo(size(), QImage::Format_RGB32);
    QPainter imgPainter(&imagenFondo);

    // Mitad superior: gradiente amarillo -> naranja -> rojo diagonal
    QLinearGradient gradSuperior(0, 0, width(), height() / 2);
    gradSuperior.setColorAt(0.0, QColor(255, 210, 0));   // amarillo
    gradSuperior.setColorAt(0.5, QColor(255, 120, 0));   // naranja
    gradSuperior.setColorAt(1.0, QColor(220, 30, 60));   // rojo
    imgPainter.fillRect(0, 0, width(), height() / 2, gradSuperior);

    // Mitad inferior: gradiente verde -> azul -> violeta diagonal
    QLinearGradient gradInferior(width(), height() / 2, 0, height());
    gradInferior.setColorAt(0.0, QColor(0, 200, 100));   // verde
    gradInferior.setColorAt(0.5, QColor(0, 80, 220));    // azul
    gradInferior.setColorAt(1.0, QColor(140, 0, 220));   // violeta
    imgPainter.fillRect(0, height() / 2, width(), height() / 2, gradInferior);

    // Banda diagonal decorativa que cruza el centro (como en la imagen)
    QLinearGradient gradBanda(width(), 0, 0, height());
    gradBanda.setColorAt(0.0, QColor(255, 180, 0, 120));
    gradBanda.setColorAt(1.0, QColor(100, 0, 200, 120));
    imgPainter.fillRect(rect(), gradBanda);

    imgPainter.end();

    // Dibujamos la imagen generada como pide la consigna: drawImage
    painter.drawImage(rect(), imagenFondo);
}

void Ventana::onBotonClicado()
{
    Boton *boton = qobject_cast<Boton*>(sender());
    if (boton) {
        QString Boton = boton->objectName();
        QMessageBox::information(this, "Clic", "Hiciste clic en el widget: " + Boton);
    }
}
