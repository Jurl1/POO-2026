#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class VentanaPrincipal : public QWidget  {
    Q_OBJECT

public:
    VentanaPrincipal( QWidget * parent = nullptr );

private:
    QLabel * lblBienvenida;
    QLabel * lblPerfil;
    QPushButton * pbPerfil;
    QPushButton * pbCerrarSesion;

    QNetworkAccessManager * nam;
    QString token;

signals:
    void cerrarSesion();

public slots:
    void slot_recibirToken( QString token );

private slots:
    void slot_obtenerPerfil();
    void slot_respuestaPerfil( QNetworkReply * reply );
    void slot_cerrarSesion();
};

#endif // VENTANAPRINCIPAL_H
