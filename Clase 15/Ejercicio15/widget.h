#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // Esta función se ejecuta al hacer clic en el botón
    void on_btnLogin_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H