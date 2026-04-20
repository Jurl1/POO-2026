#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>

class Ventana : public QWidget {
    Q_OBJECT
public:
    Ventana(QWidget *parent = nullptr);
    void iniciarDescarga(const QString &url);

signals:
    // Esta señal avisará al Login que ya puede mostrarnos
    void descargaCompletada();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_descargaFinalizada(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QImage imagenFondo;
};

#endif // VENTANA_H