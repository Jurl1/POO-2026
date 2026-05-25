#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QProgressBar>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "parser.h"

class Widget : public QWidget  {
    Q_OBJECT

public:
    Widget( QWidget * parent = nullptr );

private:
    QLineEdit * leUrl;
    QLineEdit * leDirectorio;
    QPushButton * pbDescargar;
    QPushButton * pbDirectorio;
    QListWidget * lwUrls;
    QLabel * lblEstado;
    QProgressBar * barraProgreso;

    QNetworkAccessManager * nam;
    Parser parser;

    QString directorioDestino;
    QStringList urlsRecursos;
    int totalDescargas;
    int descargasCompletadas;
    bool descargandoPagina;

private slots:
    void slot_seleccionarDirectorio();
    void slot_descargar();
    void slot_descargaFinalizada( QNetworkReply * reply );
};

#endif // WIDGET_H
