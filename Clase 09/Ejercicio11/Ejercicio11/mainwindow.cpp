#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString usuario = ui->lineEdit->text();
    QString clave = ui->lineEdit_2->text();

    if (usuario == "admin" && clave == "1234"){
        QMessageBox::information(this, "Exito", "Ingreso Correcto");
    } else {
        QMessageBox::warning(this, "Error", "Datos incorrectos");
        ui->lineEdit_2->clear();
    }
}

