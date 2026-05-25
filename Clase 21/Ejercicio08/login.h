#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Login : public QWidget  {
    Q_OBJECT

public:
    Login( QWidget * parent = nullptr );

private:
    QLineEdit * leUsuario;
    QLineEdit * leClave;
    QPushButton * pbLogin;
    QLabel * lblEstado;

    QNetworkAccessManager * nam;

signals:
    void loginExitoso( QString token );

private slots:
    void slot_login();
    void slot_respuestaLogin( QNetworkReply * reply );
};

#endif // LOGIN_H
