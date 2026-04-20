#include "login.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

Login :: Login(QWidget *parent) :
QWidget(parent){
    setWindowTitle("Sistema de Acceso");
    resize(300, 200);

    grupoBox = new QGroupBox("Ingrese sus datos");
    QLabel *lClave = new QLabel("Clave:");
    QLabel *lUsuario = new QLabel("Usuario:");
    leUsuario = new QLineEdit();
    leClave = new QLineEdit();

    leClave->setEchoMode(QLineEdit::Password);
    btnIngresar = new
        QPushButton("Ingresar");

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(lUsuario, 0, 0);
    gridLayout->addWidget(leUsuario, 0, 1);
    gridLayout->addWidget(lClave, 1, 0);
    gridLayout->addWidget(leClave, 1, 1);
    gridLayout->addWidget(btnIngresar, 2, 0, 1, 2);

    grupoBox->setLayout(gridLayout);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(grupoBox);

    connect(btnIngresar, SIGNAL(clicked()), this, SLOT(verificarCredenciales()));
}

void Login::verificarCredenciales(){
    if (leUsuario->text() == "admin" && leClave->text() == "1234") {
        QMessageBox::information(this, "Exito", "Bienvenido al sistema.");
    } else {
        QMessageBox::warning(this, "Error", "Usuario o clave incorrectos.");
        leClave->clear();
    }
}