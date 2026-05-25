#include "widget.h"
#include "admindbmedicamentos.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

Widget::Widget( QWidget * parent ) : QWidget( parent )  {

    this->setWindowTitle( "Gestión de Medicamentos - APROSS" );
    this->resize( 500, 400 );

    QVBoxLayout * vlPrincipal = new QVBoxLayout( this );

    // ---- Sección de ingreso ----
    QHBoxLayout * hlIngreso = new QHBoxLayout;

    QLabel * lblDosis = new QLabel( "Dosis:" );
    dsbDosis = new QDoubleSpinBox;
    dsbDosis->setRange( 0.1, 1000.0 );
    dsbDosis->setDecimals( 1 );
    dsbDosis->setValue( 50.0 );

    pbAgregar = new QPushButton( "Agregar" );

    hlIngreso->addWidget( lblDosis );
    hlIngreso->addWidget( dsbDosis );
    hlIngreso->addWidget( pbAgregar );

    // ---- Lista de cajas ----
    lwCajas = new QListWidget;
    lwCajas->setSelectionMode( QAbstractItemView::MultiSelection );

    // ---- Botones inferiores ----
    QHBoxLayout * hlBotones = new QHBoxLayout;

    pbSumar = new QPushButton( "Sumar" );
    pbComparar = new QPushButton( "Comparar" );

    hlBotones->addWidget( pbSumar );
    hlBotones->addWidget( pbComparar );

    // ---- Label total ----
    lblTotal = new QLabel( "Total dosis: 0.0 / 1000" );

    // ---- Armado del layout principal ----
    vlPrincipal->addLayout( hlIngreso );
    vlPrincipal->addWidget( lwCajas );
    vlPrincipal->addLayout( hlBotones );
    vlPrincipal->addWidget( lblTotal );

    // ---- Conexiones con SIGNAL y SLOT ----
    connect( pbAgregar, SIGNAL( clicked() ), this, SLOT( slot_agregar() ) );
    connect( pbSumar, SIGNAL( clicked() ), this, SLOT( slot_sumar() ) );
    connect( pbComparar, SIGNAL( clicked() ), this, SLOT( slot_comparar() ) );

    actualizarLista();
}

void Widget::actualizarLista()  {
    lwCajas->clear();

    cajas = AdminDBMedicamentos::getInstancia()->obtenerTodas();

    for ( int i = 0; i < cajas.size(); i++ )  {
        lwCajas->addItem( cajas.at( i ).toString() );
    }

    float total = AdminDBMedicamentos::getInstancia()->obtenerTotalDosis();
    lblTotal->setText( QString( "Total dosis: %1 / 1000" )
                       .arg( QString::number( total, 'f', 1 ) ) );
}

void Widget::slot_agregar()  {
    float dosis = static_cast< float >( dsbDosis->value() );

    if ( ! AdminDBMedicamentos::getInstancia()->insertarCaja( dosis ) )  {
        QMessageBox::warning( this, "Advertencia",
                              "No se puede agregar la caja. Se excede el límite de 1000 dosis." );
        return;
    }

    actualizarLista();
}

void Widget::slot_sumar()  {
    QList< QListWidgetItem * > seleccionados = lwCajas->selectedItems();

    if ( seleccionados.size() != 2 )  {
        QMessageBox::warning( this, "Advertencia",
                              "Debe seleccionar exactamente 2 cajas para sumar." );
        return;
    }

    int indice1 = lwCajas->row( seleccionados.at( 0 ) );
    int indice2 = lwCajas->row( seleccionados.at( 1 ) );

    CajaMedicamento combinada = cajas.at( indice1 ) + cajas.at( indice2 );

    qDebug() << "Resultado de la suma:" << combinada.toString();

    if ( ! AdminDBMedicamentos::getInstancia()->insertarCaja( combinada.getDosisTotales() ) )  {
        QMessageBox::warning( this, "Advertencia",
                              "No se puede agregar la caja combinada. Se excede el límite de 1000 dosis." );
        return;
    }

    actualizarLista();
}

void Widget::slot_comparar()  {
    QList< QListWidgetItem * > seleccionados = lwCajas->selectedItems();

    if ( seleccionados.size() != 2 )  {
        QMessageBox::warning( this, "Advertencia",
                              "Debe seleccionar exactamente 2 cajas para comparar." );
        return;
    }

    int indice1 = lwCajas->row( seleccionados.at( 0 ) );
    int indice2 = lwCajas->row( seleccionados.at( 1 ) );

    CajaMedicamento caja1 = cajas.at( indice1 );
    CajaMedicamento caja2 = cajas.at( indice2 );

    if ( caja1 == caja2 )  {
        qDebug() << caja1.toString() << "y" << caja2.toString()
                 << "tienen la MISMA cantidad de dosis.";
    }
    else  {
        qDebug() << caja1.toString() << "y" << caja2.toString()
                 << "tienen DIFERENTE cantidad de dosis.";
    }
}
