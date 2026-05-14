#ifndef BOTON_H
#define BOTON_H

#include <QWidget>

namespace Ui {
class Boton;
}

class Boton : public QWidget
{
    Q_OBJECT

public:
    // Enumeracion de colores segun la consigna
    enum Color { Azul, Verde, Magenta };

    explicit Boton(QWidget *parent = nullptr);
    ~Boton();

    // Metodo requerido por la consigna: boton->colorear(Boton::Azul)
    void colorear(Color c);

    // Texto que se muestra sobre el boton
    void setTexto(const QString &texto);

signals:
    void signal_clic();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Boton *ui;
    Color   colorActual;
    QString m_texto;
};

#endif // BOTON_H
