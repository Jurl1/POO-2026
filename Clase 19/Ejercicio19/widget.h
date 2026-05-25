#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>

#include "cajamedicamento.h"

class Widget : public QWidget  {
    Q_OBJECT

public:
    Widget( QWidget * parent = nullptr );

private:
    QDoubleSpinBox * dsbDosis;
    QPushButton * pbAgregar;
    QPushButton * pbSumar;
    QPushButton * pbComparar;
    QListWidget * lwCajas;
    QLabel * lblTotal;

    QList< CajaMedicamento > cajas;

    void actualizarLista();

private slots:
    void slot_agregar();
    void slot_sumar();
    void slot_comparar();
};

#endif // WIDGET_H
