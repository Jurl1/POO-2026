#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Principal : public QWidget {
    Q_OBJECT
public:
    Principal(QWidget *parent = nullptr);

private slots:
    void slot_descargar();
    void slot_descargaFinalizada(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QLineEdit *leUrl;
    QLabel *lImagen;
    QPushButton *pbDescargar;
};

#endif // PRINCIPAL_H