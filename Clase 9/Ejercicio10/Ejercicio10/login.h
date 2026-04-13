#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>

class Login : public QWidget {
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);

private slots:
    void verificarCredenciales();

private:
    QGroupBox *grupoBox;
    QLineEdit *leUsuario;
    QLineEdit *leClave;
    QPushButton *btnIngresar;
};

#endif