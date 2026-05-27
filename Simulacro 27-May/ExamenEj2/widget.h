#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "imagenconetiqueta.h"

class Widget : public QWidget  {
    Q_OBJECT

public:
    Widget( QWidget * parent = nullptr );

private:
    QLineEdit * leEtiqueta;
    QComboBox * cbTipo;
    QGridLayout * glGaleria;

    QPushButton * botones[ 3 ][ 3 ];

    int buscarFila( QPushButton * boton );
    int buscarColumna( QPushButton * boton );

private slots:
    void slot_agregarImagen();
};

#endif // WIDGET_H
