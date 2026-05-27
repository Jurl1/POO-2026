#include "widget.h"
#include "imagennormal.h"
#include "imagenconmarco.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

Widget::Widget( QWidget * parent ) : QWidget( parent )  {
    this->setWindowTitle( "Galería de Imágenes con Etiquetas" );
    this->resize( 700, 750 );

    QVBoxLayout * vlPrincipal = new QVBoxLayout( this );

    // ---- Barra superior ----
    QHBoxLayout * hlBarra = new QHBoxLayout;

    QLabel * lblEtiqueta = new QLabel( "Etiqueta:" );
    leEtiqueta = new QLineEdit;
    leEtiqueta->setPlaceholderText( "Ingrese la etiqueta para la imagen" );

    QLabel * lblTipo = new QLabel( "Tipo:" );
    cbTipo = new QComboBox;
    cbTipo->addItem( "Normal" );
    cbTipo->addItem( "Con Marco" );

    hlBarra->addWidget( lblEtiqueta );
    hlBarra->addWidget( leEtiqueta );
    hlBarra->addWidget( lblTipo );
    hlBarra->addWidget( cbTipo );

    vlPrincipal->addLayout( hlBarra );

    // ---- Grilla 3x3 ----
    glGaleria = new QGridLayout;
    glGaleria->setSpacing( 8 );

    for ( int fila = 0; fila < 3; fila++ )  {
        for ( int col = 0; col < 3; col++ )  {
            botones[ fila ][ col ] = new QPushButton( "Agregar\nimagen" );
            botones[ fila ][ col ]->setMinimumSize( 200, 200 );
            botones[ fila ][ col ]->setMaximumSize( 250, 250 );

            // row offset +1 por la barra superior
            glGaleria->addWidget( botones[ fila ][ col ], fila, col );

            connect( botones[ fila ][ col ], SIGNAL( clicked() ),
                     this, SLOT( slot_agregarImagen() ) );
        }
    }

    vlPrincipal->addLayout( glGaleria );
}

int Widget::buscarFila( QPushButton * boton )  {
    for ( int f = 0; f < 3; f++ )
        for ( int c = 0; c < 3; c++ )
            if ( botones[ f ][ c ] == boton )
                return f;
    return -1;
}

int Widget::buscarColumna( QPushButton * boton )  {
    for ( int f = 0; f < 3; f++ )
        for ( int c = 0; c < 3; c++ )
            if ( botones[ f ][ c ] == boton )
                return c;
    return -1;
}

void Widget::slot_agregarImagen()  {
    QPushButton * boton = qobject_cast< QPushButton * >( sender() );
    if ( ! boton )
        return;

    // Validar que se haya ingresado una etiqueta
    QString etiqueta = leEtiqueta->text().trimmed();
    if ( etiqueta.isEmpty() )  {
        QMessageBox::warning( this, "Advertencia",
                              "Ingrese una etiqueta antes de agregar la imagen." );
        return;
    }

    // Abrir diálogo para seleccionar imagen
    QString ruta = QFileDialog::getOpenFileName( this, "Seleccionar imagen", ".",
                                                  "Imágenes (*.png *.jpg *.jpeg *.bmp *.gif)" );

    if ( ruta.isEmpty() )
        return;

    int fila = buscarFila( boton );
    int col  = buscarColumna( boton );

    if ( fila == -1 || col == -1 )
        return;

    // Crear la imagen según el tipo seleccionado
    ImagenConEtiqueta * imagen = nullptr;

    if ( cbTipo->currentIndex() == 0 )  {
        imagen = new ImagenNormal( ruta, etiqueta, this );
    }
    else  {
        imagen = new ImagenConMarco( ruta, etiqueta, this );
    }

    imagen->setMinimumSize( 200, 200 );
    imagen->setMaximumSize( 250, 250 );

    // Polimorfismo: llamar a mostrar() a través de puntero base
    imagen->mostrar();

    // Reemplazar el botón por la imagen en la grilla
    glGaleria->removeWidget( boton );
    boton->hide();
    boton->deleteLater();
    botones[ fila ][ col ] = nullptr;

    glGaleria->addWidget( imagen, fila, col );

    qDebug() << "Imagen agregada en [" << fila << "," << col << "]"
             << "- Tipo:" << cbTipo->currentText()
             << "- Etiqueta:" << etiqueta;
}
