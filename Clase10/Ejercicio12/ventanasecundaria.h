#ifndef VENTANASECUNDARIA_H
#define VENTANASECUNDARIA_H

#include <QWidget>

namespace Ui {
class VentanaSecundaria;
}

class VentanaSecundaria : public QWidget
{
    Q_OBJECT

public:
    explicit VentanaSecundaria(QWidget *parent = nullptr);
    ~VentanaSecundaria();

private:
    Ui::VentanaSecundaria *ui;
};

#endif // VENTANASECUNDARIA_H
