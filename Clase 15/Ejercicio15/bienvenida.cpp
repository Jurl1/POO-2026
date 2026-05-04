#include "bienvenida.h"
#include "ui_bienvenida.h"

Bienvenida::Bienvenida(QString usuario, QString fecha, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bienvenida)
{
    ui->setupUi(this);

    // Escribimos los datos en las etiquetas que creaste
    ui->lblNombre->setText("¡Hola, " + usuario + "!");

    if (fecha.isEmpty()) {
        ui->lblFecha->setText("Este es tu primer ingreso.");
    } else {
        ui->lblFecha->setText("Último ingreso: " + fecha);
    }
}

Bienvenida::~Bienvenida() {
    delete ui;
}