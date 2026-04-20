#include "LoginYFormulario.h"
#include <QMessageBox>

// --- Constructor del Formulario ---
Formulario::Formulario(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Formulario");
    resize(300, 150);

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel("Legajo:"), 0, 0);
    layout->addWidget(new QLineEdit(), 0, 1);

    layout->addWidget(new QLabel("Nombre:"), 1, 0);
    layout->addWidget(new QLineEdit(), 1, 1);

    layout->addWidget(new QLabel("Apellido:"), 2, 0);
    layout->addWidget(new QLineEdit(), 2, 1);

    QPushButton *btnGuardar = new QPushButton("Guardar");
    layout->addWidget(btnGuardar, 3, 0, 1, 2);
}

// --- Constructor del Login ---
Login::Login(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Login");

    ventanaFormulario = new Formulario(); // Lo creamos pero no lo mostramos aún

    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel("Usuario:"), 0, 0);
    leUsuario = new QLineEdit();
    layout->addWidget(leUsuario, 0, 1);

    layout->addWidget(new QLabel("Clave:"), 1, 0);
    leClave = new QLineEdit();
    leClave->setEchoMode(QLineEdit::Password); // Modo contraseña
    layout->addWidget(leClave, 1, 1);

    QPushButton *btnIngresar = new QPushButton("Ingresar");
    layout->addWidget(btnIngresar, 2, 0, 1, 2);

    // Conectar el botón y el Enter al slot de validación
    connect(btnIngresar, SIGNAL(clicked()), this, SLOT(validarCredenciales()));
    connect(leClave, SIGNAL(returnPressed()), this, SLOT(validarCredenciales()));
}

// --- Validación ---
void Login::validarCredenciales() {
    if (leUsuario->text() == "admin" && leClave->text() == "1111") {
        this->close();
        ventanaFormulario->show();
    } else {
        leClave->clear(); // Borra solo la clave si falla
        QMessageBox::warning(this, "Error", "Clave incorrecta.");
    }
}