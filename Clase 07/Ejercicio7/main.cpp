#include <QApplication>
#include "CaptchaWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CaptchaWidget *captcha = new CaptchaWidget();
    captcha->show();
    return app.exec();
}