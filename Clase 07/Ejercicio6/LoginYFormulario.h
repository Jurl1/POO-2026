#ifndef LOGINYFORMULARIO_H
#define LOGINYFORMULARIO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

// Clase para el formulario principal
class Formulario : public QWidget {
    Q_OBJECT
public:
    Formulario(QWidget *parent = nullptr);
};

// Clase para la ventana de Login
class Login : public QWidget {
    Q_OBJECT
public:
    Login(QWidget *parent = nullptr);

private slots:
    void validarCredenciales();

private:
    QLineEdit *leUsuario;
    QLineEdit *leClave;
    Formulario *ventanaFormulario;
};

#endif // LOGINYFORMULARIO_H