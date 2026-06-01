#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui  {
class Login;
}

class Login : public QWidget  {
    Q_OBJECT

public:
    Login( QWidget * parent = nullptr );
    ~Login();

signals:
    // Emitida al validar correctamente, lleva el nombre de usuario
    void signal_loginExitoso( QString usuario );

private slots:
    void slot_iniciarSesion();

private:
    Ui::Login * ui;
};

#endif // LOGIN_H
