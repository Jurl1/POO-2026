#include <QApplication>
#include "LoginYFormulario.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Login *login = new Login();
    login->show();
    return app.exec();
}