#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"
#include "dibujolibre.h"
#include "dibujoconmarco.h"
#include "admindb.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

VentanaPrincipal::VentanaPrincipal( QWidget * parent )
    : QWidget( parent ), ui( new Ui::VentanaPrincipal ), m_dibujoActual( nullptr )  {

    ui->setupUi( this );

    // Categorías predefinidas
    ui->cbCategoria->addItem( "Boceto" );
    ui->cbCategoria->addItem( "Arte" );
    ui->cbCategoria->addItem( "Diagrama" );
    ui->cbCategoria->addItem( "Otro" );

    // Tipos de dibujo (corresponden a las clases derivadas)
    ui->cbTipo->addItem( "Dibujo Libre" );
    ui->cbTipo->addItem( "Dibujo Con Marco" );

    // Crear el dibujo inicial (DibujoLibre por defecto)
    crearDibujo( 0 );

    // Conexiones SIGNAL / SLOT
    connect( ui->pbGuardar,  SIGNAL( clicked() ),
             this, SLOT( slot_guardarDibujo() ) );

    connect( ui->pbLimpiar,  SIGNAL( clicked() ),
             this, SLOT( slot_limpiar() ) );

    connect( ui->pbExportar, SIGNAL( clicked() ),
             this, SLOT( slot_exportarImagen() ) );

    connect( ui->cbTipo,     SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( slot_tipoCambiado( int ) ) );

    connect( ui->widgetLienzo, SIGNAL( signal_dibujoModificado() ),
             this, SLOT( slot_dibujoModificado() ) );
}

VentanaPrincipal::~VentanaPrincipal()  {
    // Liberar el dibujo actual para evitar memory leaks (mejora del simulacro 1)
    delete m_dibujoActual;
    delete ui;
}

// Almacena el usuario que inició sesión y actualiza el título
void VentanaPrincipal::slot_setUsuario( QString usuario )  {
    m_usuarioActual = usuario;
    setWindowTitle( "Gestor de Dibujos — " + usuario );
}

// Crea un nuevo Dibujo según el índice del combo (polimorfismo).
// Preserva los trazos del dibujo anterior si existen.
void VentanaPrincipal::crearDibujo( int tipo )  {
    QVector< QVector< QPoint > > trazosAnteriores;

    // Preservar trazos del dibujo anterior
    if ( m_dibujoActual )  {
        trazosAnteriores = m_dibujoActual->getTrazos();
        delete m_dibujoActual;
        m_dibujoActual = nullptr;
    }

    // Crear la subclase correspondiente (polimorfismo)
    if ( tipo == 0 )  {
        m_dibujoActual = new DibujoLibre;
    }
    else  {
        m_dibujoActual = new DibujoConMarco;
    }

    // Restaurar trazos
    if ( ! trazosAnteriores.isEmpty() )  {
        m_dibujoActual->setTrazos( trazosAnteriores );
    }

    // Asignar al lienzo (el lienzo no conoce el tipo concreto)
    ui->widgetLienzo->setDibujo( m_dibujoActual );
}

// Al cambiar el tipo en el combo, recrea el Dibujo preservando los trazos
void VentanaPrincipal::slot_tipoCambiado( int index )  {
    crearDibujo( index );
}

// Persiste los metadatos del dibujo en la base de datos SQLite
void VentanaPrincipal::slot_guardarDibujo()  {
    QString nombre    = ui->leNombre->text().trimmed();
    QString categoria = ui->cbCategoria->currentText();
    QString tipo      = ui->cbTipo->currentText();

    // Validar nombre no vacío
    if ( nombre.isEmpty() )  {
        QMessageBox::warning( this, "Advertencia",
                              "Ingrese un nombre para el dibujo antes de guardar." );
        return;
    }

    // Validar que el lienzo no esté vacío
    if ( m_dibujoActual && m_dibujoActual->estaVacio() )  {
        QMessageBox::warning( this, "Advertencia",
                              "El lienzo está vacío. Dibuje algo antes de guardar." );
        return;
    }

    // Guardar en base de datos
    if ( AdminDB::getInstancia()->guardarDibujo( nombre, categoria, tipo, m_usuarioActual ) )  {
        ui->lblEstado->setStyleSheet( "color: green;" );
        ui->lblEstado->setText( "Dibujo '" + nombre + "' guardado correctamente." );
        QMessageBox::information( this, "Éxito",
                                  "El dibujo fue guardado en la base de datos." );
    }
    else  {
        ui->lblEstado->setStyleSheet( "color: red;" );
        ui->lblEstado->setText( "Error al guardar el dibujo." );
        QMessageBox::critical( this, "Error",
                               "No se pudo guardar el dibujo en la base de datos." );
    }
}

// Limpia el lienzo y el campo de nombre
void VentanaPrincipal::slot_limpiar()  {
    ui->widgetLienzo->limpiarLienzo();
    ui->leNombre->clear();
    ui->lblEstado->setStyleSheet( "color: gray;" );
    ui->lblEstado->setText( "Lienzo limpiado." );
}

// Exporta el contenido del lienzo como imagen PNG o JPG
void VentanaPrincipal::slot_exportarImagen()  {
    QImage imagen = ui->widgetLienzo->exportarImagen();

    // Validar que la imagen se generó correctamente (mejora del simulacro 1)
    if ( imagen.isNull() )  {
        QMessageBox::critical( this, "Error",
                               "No se pudo generar la imagen del lienzo." );
        return;
    }

    // Seleccionar ubicación con QFileDialog
    QString ruta = QFileDialog::getSaveFileName( this, "Exportar imagen", ".",
                                                  "PNG (*.png);;JPEG (*.jpg *.jpeg)" );
    if ( ruta.isEmpty() )  {
        return;
    }

    // Guardar la imagen y dar feedback al usuario
    if ( imagen.save( ruta ) )  {
        ui->lblEstado->setStyleSheet( "color: green;" );
        ui->lblEstado->setText( "Imagen exportada correctamente." );
        QMessageBox::information( this, "Éxito",
                                  "La imagen se exportó correctamente." );
    }
    else  {
        ui->lblEstado->setStyleSheet( "color: red;" );
        ui->lblEstado->setText( "Error al exportar la imagen." );
        QMessageBox::critical( this, "Error",
                               "No se pudo guardar la imagen." );
    }
}

// Actualiza el estado cuando el usuario dibuja algo
void VentanaPrincipal::slot_dibujoModificado()  {
    ui->lblEstado->setStyleSheet( "color: orange;" );
    ui->lblEstado->setText( "Dibujo modificado (sin guardar)" );
}
