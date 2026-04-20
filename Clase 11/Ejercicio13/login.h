#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>
#include <QLineEdit>
#include <QPushButton>
#include "ventana.h"

class Login : public QWidget {
    Q_OBJECT
public:
    Login(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_descargaFondoFinalizada(QNetworkReply *reply);
    void on_btnIngresar_clicked();
    void abrirVentanaSecundaria();

private:
    QNetworkAccessManager *manager;
    QImage imagenFondo;

    QLineEdit *leUsuario;
    QLineEdit *leClave;
    QPushButton *btnIngresar;

    Ventana *ventanaSecundaria;
};

#endif // LOGIN_H