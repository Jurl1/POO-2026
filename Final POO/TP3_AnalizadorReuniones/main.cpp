#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Analizador de Reuniones");
    LoginWindow login;
    login.show();
    return a.exec();
}
