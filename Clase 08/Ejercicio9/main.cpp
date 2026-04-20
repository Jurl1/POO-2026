#include <QApplication>
#include "Principal.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Principal ventana;
    ventana.show();

    return app.exec();
}