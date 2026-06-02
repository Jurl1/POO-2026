#include <QApplication>
#include "login.h"
#include "ventanaprincipal.h"
#include "admindb.h"

#include <QMessageBox>

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    // Conectar a la base de datos con feedback visual si falla (mejora del simulacro 1)
    if ( ! AdminDB::getInstancia()->conectar() )  {
        QMessageBox::critical( nullptr, "Error de base de datos",
                               "No se pudo conectar con la base de datos SQLite.\n"
                               "Verifique que el archivo dibujos.sqlite existe." );
        return 1;
    }

    Login login;
    VentanaPrincipal principal;

    // Login exitoso: ocultar login, mostrar ventana principal y pasar el usuario
    QObject::connect( & login, SIGNAL( signal_loginExitoso( QString ) ),
                      & login, SLOT( hide() ) );

    QObject::connect( & login, SIGNAL( signal_loginExitoso( QString ) ),
                      & principal, SLOT( show() ) );

    QObject::connect( & login, SIGNAL( signal_loginExitoso( QString ) ),
                      & principal, SLOT( slot_setUsuario( QString ) ) );

    login.show();

    return a.exec();
}
