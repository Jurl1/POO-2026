#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>

namespace Ui {
class Login;
}

class Login : public QWidget  {
    Q_OBJECT

public:
    Login( QWidget * parent = nullptr );
    ~Login();

private:
    Ui::Login * ui;
    QNetworkAccessManager * m_nam;

signals:
    void loginExitoso();

private slots:
    void slot_descargarAvatar();
    void slot_avatarDescargado( QNetworkReply * reply );
    void slot_iniciarSesion();
};

#endif // LOGIN_H
