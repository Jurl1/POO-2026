/********************************************************************************
** Form generated from reading UI file 'ventanasecundaria.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANASECUNDARIA_H
#define UI_VENTANASECUNDARIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VentanaSecundaria
{
public:

    void setupUi(QWidget *VentanaSecundaria)
    {
        if (VentanaSecundaria->objectName().isEmpty())
            VentanaSecundaria->setObjectName("VentanaSecundaria");
        VentanaSecundaria->resize(400, 300);

        retranslateUi(VentanaSecundaria);

        QMetaObject::connectSlotsByName(VentanaSecundaria);
    } // setupUi

    void retranslateUi(QWidget *VentanaSecundaria)
    {
        VentanaSecundaria->setWindowTitle(QCoreApplication::translate("VentanaSecundaria", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VentanaSecundaria: public Ui_VentanaSecundaria {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANASECUNDARIA_H
