#include <QApplication>
#include "admindbmedicamentos.h"
#include "widget.h"

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    AdminDBMedicamentos::getInstancia()->conectar();

    Widget w;
    w.show();

    return a.exec();
}
