#ifndef BIENVENIDA_H
#define BIENVENIDA_H

#include <QWidget>

namespace Ui { class Bienvenida; }

class Bienvenida : public QWidget {
    Q_OBJECT

public:
    // Modificamos el constructor para que reciba los datos
    explicit Bienvenida(QString usuario, QString fecha, QWidget *parent = nullptr);
    ~Bienvenida();

private:
    Ui::Bienvenida *ui;
};

#endif // BIENVENIDA_H