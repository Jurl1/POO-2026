#ifndef CAPTCHAWIDGET_H
#define CAPTCHAWIDGET_H

#include <QWidget>
#include <QString>
#include <QLineEdit>

class CaptchaWidget : public QWidget {
    Q_OBJECT
public:
    CaptchaWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void validarCaptcha();
    void regenerarCaptcha();

private:
    QString numeroCaptcha;
    QLineEdit *leIngreso;
};

#endif // CAPTCHAWIDGET_H