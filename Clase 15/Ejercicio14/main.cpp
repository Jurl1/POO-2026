#include "pintura.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pintura ventana;
    ventana.show();

    return a.exec();
}