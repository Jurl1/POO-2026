#include "ventanaprincipal.h"
#include <QVBoxLayout>
#include <QLabel>

VentanaPrincipal::VentanaPrincipal( QWidget * parent ) : QWidget( parent )  {
    this->setWindowTitle( "Bienvenido" );
    this->resize( 400, 300 );

    QVBoxLayout * vl = new QVBoxLayout( this );
    QLabel * lbl = new QLabel( "Sesión iniciada correctamente.", this );
    lbl->setAlignment( Qt::AlignCenter );
    vl->addWidget( lbl );
}
