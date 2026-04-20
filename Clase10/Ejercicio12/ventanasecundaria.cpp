#include "ventanasecundaria.h"
#include "ui_ventanasecundaria.h"

VentanaSecundaria::VentanaSecundaria(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VentanaSecundaria)
{
    ui->setupUi(this);
}

VentanaSecundaria::~VentanaSecundaria()
{
    delete ui;
}
