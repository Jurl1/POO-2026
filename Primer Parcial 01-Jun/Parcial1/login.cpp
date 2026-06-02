#include "login.h"
#include "ui_login.h"
#include "admindb.h"

#include <QMessageBox>
#include <QDebug>

Login::Login( QWidget * parent ) : QWidget( parent ), ui( new Ui::Login )  {
    ui->setupUi( this );

    connect( ui->pbLogin, SIGNAL( clicked() ),
             this, SLOT( slot_iniciarSesion() ) );
}

Login::~Login()  {
    delete ui;
}

// Valida credenciales contra la DB. Muestra feedback visual al usuario
// tanto para errores de campo vacío como para credenciales incorrectas.
void Login::slot_iniciarSesion()  {
    QString usuario = ui->leUsuario->text().trimmed();
    QString clave   = ui->leClave->text();

    // Validar campos vacíos
    if ( usuario.isEmpty() || clave.isEmpty() )  {
        ui->lblEstado->setStyleSheet( "color: red;" );
        ui->lblEstado->setText( "Complete ambos campos." );
        return;
    }

    // Validar contra la base de datos
    if ( AdminDB::getInstancia()->validarUsuario( usuario, clave ) )  {
        AdminDB::getInstancia()->registrarLogin( usuario );
        ui->lblEstado->setText( "" );
        emit signal_loginExitoso( usuario );
    }
    else  {
        ui->lblEstado->setStyleSheet( "color: red;" );
        ui->lblEstado->setText( "Usuario o clave incorrectos." );
        ui->leClave->clear();

        // Feedback visual al usuario (mejora del simulacro 1)
        QMessageBox::warning( this, "Error de autenticación",
                              "El usuario o la clave ingresados no son válidos." );
    }
}
