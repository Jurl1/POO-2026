#include <QApplication>
#include "login.h"
#include "ventanaprincipal.h"
#include "admindb.h"

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    AdminDB::getInstancia()->conectar();

    Login * login = new Login;
    VentanaPrincipal * principal = new VentanaPrincipal;

    QObject::connect( login, SIGNAL( loginExitoso() ),
                      login, SLOT( hide() ) );

    QObject::connect( login, SIGNAL( loginExitoso() ),
                      principal, SLOT( show() ) );

    login->show();

    return a.exec();
}
