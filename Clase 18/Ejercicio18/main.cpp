#include "juego.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Juego w;
    w.setWindowTitle("T-Rex Extremo - POO");
    w.show();
    return a.exec();
}