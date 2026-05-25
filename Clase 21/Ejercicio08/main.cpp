#include <QApplication>
#include "login.h"
#include "ventanaprincipal.h"

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    Login * login = new Login;
    VentanaPrincipal * principal = new VentanaPrincipal;

    // Login exitoso -> Ventana Principal recibe el token y se muestra
    QObject::connect( login, SIGNAL( loginExitoso( QString ) ),
                      principal, SLOT( slot_recibirToken( QString ) ) );

    // Cerrar sesión -> Vuelve a mostrarse el Login
    QObject::connect( principal, SIGNAL( cerrarSesion() ),
                      login, SLOT( show() ) );

    login->show();

    return a.exec();
}
