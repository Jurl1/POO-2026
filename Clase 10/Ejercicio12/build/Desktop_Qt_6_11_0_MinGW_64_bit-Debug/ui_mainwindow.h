/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEditUsuario;
    QLineEdit *lineEditClave;
    QPushButton *btnIngresar;
    QLabel *labelTemp;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEditUsuario = new QLineEdit(centralwidget);
        lineEditUsuario->setObjectName("lineEditUsuario");
        lineEditUsuario->setGeometry(QRect(110, 180, 113, 28));
        lineEditClave = new QLineEdit(centralwidget);
        lineEditClave->setObjectName("lineEditClave");
        lineEditClave->setGeometry(QRect(110, 310, 113, 28));
        lineEditClave->setEchoMode(QLineEdit::EchoMode::Password);
        btnIngresar = new QPushButton(centralwidget);
        btnIngresar->setObjectName("btnIngresar");
        btnIngresar->setGeometry(QRect(120, 390, 90, 29));
        labelTemp = new QLabel(centralwidget);
        labelTemp->setObjectName("labelTemp");
        labelTemp->setGeometry(QRect(80, 460, 191, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnIngresar->setText(QCoreApplication::translate("MainWindow", "Ingresar", nullptr));
        labelTemp->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
