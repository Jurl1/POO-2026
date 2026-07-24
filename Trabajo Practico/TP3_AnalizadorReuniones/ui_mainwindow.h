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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *layoutPrincipal;
    QFrame *frameHeader;
    QHBoxLayout *layoutHeader;
    QLabel *lblAppTitle;
    QSpacerItem *spacerHeader;
    QLabel *lblEstadisticas;
    QLabel *lblAppSubtitle;
    QFrame *frameControles;
    QHBoxLayout *layoutControles;
    QLabel *lblTema;
    QLineEdit *txtTema;
    QLabel *lblApiKey;
    QLineEdit *txtApiKey;
    QTabWidget *tabWidget;
    QWidget *tabTranscripcion;
    QVBoxLayout *layoutTab1;
    QFrame *frameDropZone;
    QHBoxLayout *layoutDropZone;
    QLabel *lblDropHint;
    QPushButton *btnCargarArchivo;
    QPlainTextEdit *txtTranscripcion;
    QPushButton *btnAnalizar;
    QWidget *tabResultados;
    QVBoxLayout *layoutTab2;
    QTabWidget *tabResultadosInterno;
    QWidget *subTabResumen;
    QVBoxLayout *layoutSubResumen;
    QPlainTextEdit *txtResumen;
    QWidget *subTabActa;
    QVBoxLayout *layoutSubActa;
    QPlainTextEdit *txtActa;
    QWidget *subTabTareas;
    QVBoxLayout *layoutSubTareas;
    QPlainTextEdit *txtTareas;
    QPushButton *btnExportarPDF;
    QWidget *tabHistorial;
    QVBoxLayout *layoutTab3;
    QHBoxLayout *layoutHeaderHistorial;
    QLabel *lblTituloHistorial;
    QSpacerItem *spacerHistorial;
    QPushButton *btnRefrescarHistorial;
    QSplitter *splitterHistorial;
    QListWidget *listHistorial;
    QWidget *widgetDetalleHistorial;
    QVBoxLayout *layoutDetalleHistorial;
    QTabWidget *tabDetalleHistorialInterno;
    QWidget *subTabHistorialResumen;
    QVBoxLayout *layoutHistorialResumen;
    QPlainTextEdit *txtHistorialResumen;
    QWidget *subTabHistorialActa;
    QVBoxLayout *layoutHistorialActa;
    QPlainTextEdit *txtHistorialActa;
    QWidget *subTabHistorialTareas;
    QVBoxLayout *layoutHistorialTareas;
    QPlainTextEdit *txtHistorialTareas;
    QPushButton *btnExportarHistorialPDF;
    QWidget *tabPerfil;
    QVBoxLayout *layoutTab4;
    QGroupBox *groupPerfilUsuario;
    QVBoxLayout *layoutPerfilInfo;
    QLabel *lblPerfilUsuario;
    QLabel *lblPerfilEstado;
    QGroupBox *groupPerfilApiKey;
    QVBoxLayout *layoutPerfilApiKey;
    QLabel *lblPerfilApiKeyHint;
    QHBoxLayout *layoutPerfilApiKeyInput;
    QLineEdit *txtPerfilApiKey;
    QPushButton *btnGuardarApiKey;
    QLabel *lblPerfilApiKeyError;
    QGroupBox *groupPerfilSesion;
    QVBoxLayout *layoutPerfilSesion;
    QPushButton *btnCerrarSesion;
    QSpacerItem *spacerPerfil;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1100, 780);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutPrincipal = new QVBoxLayout(centralwidget);
        layoutPrincipal->setSpacing(0);
        layoutPrincipal->setObjectName("layoutPrincipal");
        frameHeader = new QFrame(centralwidget);
        frameHeader->setObjectName("frameHeader");
        layoutHeader = new QHBoxLayout(frameHeader);
        layoutHeader->setObjectName("layoutHeader");
        lblAppTitle = new QLabel(frameHeader);
        lblAppTitle->setObjectName("lblAppTitle");

        layoutHeader->addWidget(lblAppTitle);

        spacerHeader = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutHeader->addItem(spacerHeader);

        lblEstadisticas = new QLabel(frameHeader);
        lblEstadisticas->setObjectName("lblEstadisticas");

        layoutHeader->addWidget(lblEstadisticas);

        lblAppSubtitle = new QLabel(frameHeader);
        lblAppSubtitle->setObjectName("lblAppSubtitle");

        layoutHeader->addWidget(lblAppSubtitle);


        layoutPrincipal->addWidget(frameHeader);

        frameControles = new QFrame(centralwidget);
        frameControles->setObjectName("frameControles");
        layoutControles = new QHBoxLayout(frameControles);
        layoutControles->setObjectName("layoutControles");
        lblTema = new QLabel(frameControles);
        lblTema->setObjectName("lblTema");

        layoutControles->addWidget(lblTema);

        txtTema = new QLineEdit(frameControles);
        txtTema->setObjectName("txtTema");

        layoutControles->addWidget(txtTema);

        lblApiKey = new QLabel(frameControles);
        lblApiKey->setObjectName("lblApiKey");

        layoutControles->addWidget(lblApiKey);

        txtApiKey = new QLineEdit(frameControles);
        txtApiKey->setObjectName("txtApiKey");
        txtApiKey->setEchoMode(QLineEdit::EchoMode::Password);

        layoutControles->addWidget(txtApiKey);


        layoutPrincipal->addWidget(frameControles);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setDocumentMode(true);
        tabTranscripcion = new QWidget();
        tabTranscripcion->setObjectName("tabTranscripcion");
        layoutTab1 = new QVBoxLayout(tabTranscripcion);
        layoutTab1->setSpacing(10);
        layoutTab1->setObjectName("layoutTab1");
        layoutTab1->setContentsMargins(16, 16, 16, 16);
        frameDropZone = new QFrame(tabTranscripcion);
        frameDropZone->setObjectName("frameDropZone");
        layoutDropZone = new QHBoxLayout(frameDropZone);
        layoutDropZone->setObjectName("layoutDropZone");
        lblDropHint = new QLabel(frameDropZone);
        lblDropHint->setObjectName("lblDropHint");
        lblDropHint->setAlignment(Qt::AlignmentFlag::AlignCenter);

        layoutDropZone->addWidget(lblDropHint);

        btnCargarArchivo = new QPushButton(frameDropZone);
        btnCargarArchivo->setObjectName("btnCargarArchivo");

        layoutDropZone->addWidget(btnCargarArchivo);


        layoutTab1->addWidget(frameDropZone);

        txtTranscripcion = new QPlainTextEdit(tabTranscripcion);
        txtTranscripcion->setObjectName("txtTranscripcion");
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        txtTranscripcion->setFont(font);

        layoutTab1->addWidget(txtTranscripcion);

        btnAnalizar = new QPushButton(tabTranscripcion);
        btnAnalizar->setObjectName("btnAnalizar");
        btnAnalizar->setMinimumSize(QSize(0, 48));

        layoutTab1->addWidget(btnAnalizar);

        tabWidget->addTab(tabTranscripcion, QString());
        tabResultados = new QWidget();
        tabResultados->setObjectName("tabResultados");
        layoutTab2 = new QVBoxLayout(tabResultados);
        layoutTab2->setSpacing(10);
        layoutTab2->setObjectName("layoutTab2");
        layoutTab2->setContentsMargins(16, 16, 16, 16);
        tabResultadosInterno = new QTabWidget(tabResultados);
        tabResultadosInterno->setObjectName("tabResultadosInterno");
        tabResultadosInterno->setDocumentMode(true);
        subTabResumen = new QWidget();
        subTabResumen->setObjectName("subTabResumen");
        layoutSubResumen = new QVBoxLayout(subTabResumen);
        layoutSubResumen->setObjectName("layoutSubResumen");
        layoutSubResumen->setContentsMargins(12, 12, 12, 12);
        txtResumen = new QPlainTextEdit(subTabResumen);
        txtResumen->setObjectName("txtResumen");
        txtResumen->setReadOnly(true);

        layoutSubResumen->addWidget(txtResumen);

        tabResultadosInterno->addTab(subTabResumen, QString());
        subTabActa = new QWidget();
        subTabActa->setObjectName("subTabActa");
        layoutSubActa = new QVBoxLayout(subTabActa);
        layoutSubActa->setObjectName("layoutSubActa");
        layoutSubActa->setContentsMargins(12, 12, 12, 12);
        txtActa = new QPlainTextEdit(subTabActa);
        txtActa->setObjectName("txtActa");
        txtActa->setReadOnly(true);

        layoutSubActa->addWidget(txtActa);

        tabResultadosInterno->addTab(subTabActa, QString());
        subTabTareas = new QWidget();
        subTabTareas->setObjectName("subTabTareas");
        layoutSubTareas = new QVBoxLayout(subTabTareas);
        layoutSubTareas->setObjectName("layoutSubTareas");
        layoutSubTareas->setContentsMargins(12, 12, 12, 12);
        txtTareas = new QPlainTextEdit(subTabTareas);
        txtTareas->setObjectName("txtTareas");
        txtTareas->setFont(font);
        txtTareas->setReadOnly(true);

        layoutSubTareas->addWidget(txtTareas);

        tabResultadosInterno->addTab(subTabTareas, QString());

        layoutTab2->addWidget(tabResultadosInterno);

        btnExportarPDF = new QPushButton(tabResultados);
        btnExportarPDF->setObjectName("btnExportarPDF");
        btnExportarPDF->setEnabled(false);
        btnExportarPDF->setMinimumSize(QSize(0, 48));

        layoutTab2->addWidget(btnExportarPDF);

        tabWidget->addTab(tabResultados, QString());
        tabHistorial = new QWidget();
        tabHistorial->setObjectName("tabHistorial");
        layoutTab3 = new QVBoxLayout(tabHistorial);
        layoutTab3->setSpacing(10);
        layoutTab3->setObjectName("layoutTab3");
        layoutTab3->setContentsMargins(16, 16, 16, 16);
        layoutHeaderHistorial = new QHBoxLayout();
        layoutHeaderHistorial->setObjectName("layoutHeaderHistorial");
        lblTituloHistorial = new QLabel(tabHistorial);
        lblTituloHistorial->setObjectName("lblTituloHistorial");

        layoutHeaderHistorial->addWidget(lblTituloHistorial);

        spacerHistorial = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        layoutHeaderHistorial->addItem(spacerHistorial);

        btnRefrescarHistorial = new QPushButton(tabHistorial);
        btnRefrescarHistorial->setObjectName("btnRefrescarHistorial");

        layoutHeaderHistorial->addWidget(btnRefrescarHistorial);


        layoutTab3->addLayout(layoutHeaderHistorial);

        splitterHistorial = new QSplitter(tabHistorial);
        splitterHistorial->setObjectName("splitterHistorial");
        splitterHistorial->setOrientation(Qt::Orientation::Horizontal);
        listHistorial = new QListWidget(splitterHistorial);
        listHistorial->setObjectName("listHistorial");
        splitterHistorial->addWidget(listHistorial);
        widgetDetalleHistorial = new QWidget(splitterHistorial);
        widgetDetalleHistorial->setObjectName("widgetDetalleHistorial");
        layoutDetalleHistorial = new QVBoxLayout(widgetDetalleHistorial);
        layoutDetalleHistorial->setObjectName("layoutDetalleHistorial");
        layoutDetalleHistorial->setContentsMargins(0, 0, 0, 0);
        tabDetalleHistorialInterno = new QTabWidget(widgetDetalleHistorial);
        tabDetalleHistorialInterno->setObjectName("tabDetalleHistorialInterno");
        tabDetalleHistorialInterno->setDocumentMode(true);
        subTabHistorialResumen = new QWidget();
        subTabHistorialResumen->setObjectName("subTabHistorialResumen");
        layoutHistorialResumen = new QVBoxLayout(subTabHistorialResumen);
        layoutHistorialResumen->setObjectName("layoutHistorialResumen");
        txtHistorialResumen = new QPlainTextEdit(subTabHistorialResumen);
        txtHistorialResumen->setObjectName("txtHistorialResumen");
        txtHistorialResumen->setReadOnly(true);

        layoutHistorialResumen->addWidget(txtHistorialResumen);

        tabDetalleHistorialInterno->addTab(subTabHistorialResumen, QString());
        subTabHistorialActa = new QWidget();
        subTabHistorialActa->setObjectName("subTabHistorialActa");
        layoutHistorialActa = new QVBoxLayout(subTabHistorialActa);
        layoutHistorialActa->setObjectName("layoutHistorialActa");
        txtHistorialActa = new QPlainTextEdit(subTabHistorialActa);
        txtHistorialActa->setObjectName("txtHistorialActa");
        txtHistorialActa->setReadOnly(true);

        layoutHistorialActa->addWidget(txtHistorialActa);

        tabDetalleHistorialInterno->addTab(subTabHistorialActa, QString());
        subTabHistorialTareas = new QWidget();
        subTabHistorialTareas->setObjectName("subTabHistorialTareas");
        layoutHistorialTareas = new QVBoxLayout(subTabHistorialTareas);
        layoutHistorialTareas->setObjectName("layoutHistorialTareas");
        txtHistorialTareas = new QPlainTextEdit(subTabHistorialTareas);
        txtHistorialTareas->setObjectName("txtHistorialTareas");
        txtHistorialTareas->setReadOnly(true);

        layoutHistorialTareas->addWidget(txtHistorialTareas);

        tabDetalleHistorialInterno->addTab(subTabHistorialTareas, QString());

        layoutDetalleHistorial->addWidget(tabDetalleHistorialInterno);

        btnExportarHistorialPDF = new QPushButton(widgetDetalleHistorial);
        btnExportarHistorialPDF->setObjectName("btnExportarHistorialPDF");
        btnExportarHistorialPDF->setEnabled(false);
        btnExportarHistorialPDF->setMinimumSize(QSize(0, 40));

        layoutDetalleHistorial->addWidget(btnExportarHistorialPDF);

        splitterHistorial->addWidget(widgetDetalleHistorial);

        layoutTab3->addWidget(splitterHistorial);

        tabWidget->addTab(tabHistorial, QString());
        tabPerfil = new QWidget();
        tabPerfil->setObjectName("tabPerfil");
        layoutTab4 = new QVBoxLayout(tabPerfil);
        layoutTab4->setSpacing(16);
        layoutTab4->setObjectName("layoutTab4");
        layoutTab4->setContentsMargins(24, 24, 24, 24);
        groupPerfilUsuario = new QGroupBox(tabPerfil);
        groupPerfilUsuario->setObjectName("groupPerfilUsuario");
        layoutPerfilInfo = new QVBoxLayout(groupPerfilUsuario);
        layoutPerfilInfo->setObjectName("layoutPerfilInfo");
        lblPerfilUsuario = new QLabel(groupPerfilUsuario);
        lblPerfilUsuario->setObjectName("lblPerfilUsuario");

        layoutPerfilInfo->addWidget(lblPerfilUsuario);

        lblPerfilEstado = new QLabel(groupPerfilUsuario);
        lblPerfilEstado->setObjectName("lblPerfilEstado");

        layoutPerfilInfo->addWidget(lblPerfilEstado);


        layoutTab4->addWidget(groupPerfilUsuario);

        groupPerfilApiKey = new QGroupBox(tabPerfil);
        groupPerfilApiKey->setObjectName("groupPerfilApiKey");
        layoutPerfilApiKey = new QVBoxLayout(groupPerfilApiKey);
        layoutPerfilApiKey->setSpacing(10);
        layoutPerfilApiKey->setObjectName("layoutPerfilApiKey");
        lblPerfilApiKeyHint = new QLabel(groupPerfilApiKey);
        lblPerfilApiKeyHint->setObjectName("lblPerfilApiKeyHint");

        layoutPerfilApiKey->addWidget(lblPerfilApiKeyHint);

        layoutPerfilApiKeyInput = new QHBoxLayout();
        layoutPerfilApiKeyInput->setObjectName("layoutPerfilApiKeyInput");
        txtPerfilApiKey = new QLineEdit(groupPerfilApiKey);
        txtPerfilApiKey->setObjectName("txtPerfilApiKey");
        txtPerfilApiKey->setEchoMode(QLineEdit::EchoMode::Password);

        layoutPerfilApiKeyInput->addWidget(txtPerfilApiKey);

        btnGuardarApiKey = new QPushButton(groupPerfilApiKey);
        btnGuardarApiKey->setObjectName("btnGuardarApiKey");

        layoutPerfilApiKeyInput->addWidget(btnGuardarApiKey);


        layoutPerfilApiKey->addLayout(layoutPerfilApiKeyInput);

        lblPerfilApiKeyError = new QLabel(groupPerfilApiKey);
        lblPerfilApiKeyError->setObjectName("lblPerfilApiKeyError");

        layoutPerfilApiKey->addWidget(lblPerfilApiKeyError);


        layoutTab4->addWidget(groupPerfilApiKey);

        groupPerfilSesion = new QGroupBox(tabPerfil);
        groupPerfilSesion->setObjectName("groupPerfilSesion");
        layoutPerfilSesion = new QVBoxLayout(groupPerfilSesion);
        layoutPerfilSesion->setObjectName("layoutPerfilSesion");
        btnCerrarSesion = new QPushButton(groupPerfilSesion);
        btnCerrarSesion->setObjectName("btnCerrarSesion");
        btnCerrarSesion->setMinimumSize(QSize(0, 42));

        layoutPerfilSesion->addWidget(btnCerrarSesion);


        layoutTab4->addWidget(groupPerfilSesion);

        spacerPerfil = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        layoutTab4->addItem(spacerPerfil);

        tabWidget->addTab(tabPerfil, QString());

        layoutPrincipal->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Analizador de Reuniones", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "QMainWindow, QWidget#centralwidget { background-color: #0e0e0f; }\n"
"QWidget { color: #e8e6e0; font-family: \"Segoe UI\"; font-size: 13px; }\n"
"QTabWidget::pane { border: 1px solid #2a2a2e; background-color: #141416; }\n"
"QTabBar::tab { background-color: #0e0e0f; color: #6b6b70; padding: 10px 28px; border: none; border-bottom: 2px solid transparent; font-size: 12px; letter-spacing: 1px; }\n"
"QTabBar::tab:selected { color: #f0a500; border-bottom: 2px solid #f0a500; background-color: #141416; }\n"
"QTabBar::tab:hover:!selected { color: #c8c6c0; }\n"
"QPlainTextEdit { background-color: #111113; border: 1px solid #2a2a2e; border-radius: 4px; color: #d8d6d0; padding: 10px; selection-background-color: #f0a500; selection-color: #0e0e0f; }\n"
"QPlainTextEdit:focus { border: 1px solid #f0a500; }\n"
"QLineEdit { background-color: #111113; border: 1px solid #2a2a2e; border-radius: 4px; color: #e8e6e0; padding: 6px 10px; }\n"
"QLineEdit:focus { border: 1px solid #f0a500; }\n"
"QGroupBox { border: 1px solid #2a2a2e; bo"
                        "rder-radius: 4px; margin-top: 14px; padding-top: 8px; font-size: 11px; letter-spacing: 1px; color: #6b6b70; }\n"
"QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 6px; }\n"
"QScrollBar:vertical { background: #111113; width: 8px; border: none; }\n"
"QScrollBar::handle:vertical { background: #2a2a2e; border-radius: 4px; min-height: 20px; }\n"
"QScrollBar::handle:vertical:hover { background: #f0a500; }\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }\n"
"QStatusBar { background-color: #0a0a0b; color: #6b6b70; border-top: 1px solid #2a2a2e; font-size: 11px; }\n"
"QFrame#frameHeader { background-color: #0a0a0b; border-bottom: 1px solid #f0a500; }\n"
"QFrame#frameControles { background-color: #0a0a0b; border-bottom: 1px solid #2a2a2e; }\n"
"QLabel#lblAppTitle { color: #f0a500; font-size: 18px; font-weight: bold; letter-spacing: 3px; }\n"
"QLabel#lblAppSubtitle { color: #6b6b70; font-size: 11px; letter-spacing: 1px; }\n"
"QLabel#lblTema { color: #6b6b70; font-size:"
                        " 11px; letter-spacing: 1px; }\n"
"QLabel#lblApiKey { color: #6b6b70; font-size: 11px; letter-spacing: 1px; }\n"
"QLabel#lblEstadisticas { color: #4a4a50; font-size: 10px; letter-spacing: 1px; }\n"
"QFrame#frameDropZone { border: 2px dashed #2a2a2e; border-radius: 6px; background-color: #0d0d0f; }", nullptr));
        lblAppTitle->setText(QCoreApplication::translate("MainWindow", "ANALIZADOR DE REUNIONES", nullptr));
        lblEstadisticas->setText(QCoreApplication::translate("MainWindow", "Analisis en esta sesion: 0", nullptr));
        lblAppSubtitle->setText(QCoreApplication::translate("MainWindow", "  POWERED BY GEMINI 2.5", nullptr));
        lblTema->setText(QCoreApplication::translate("MainWindow", "TEMA", nullptr));
        txtTema->setPlaceholderText(QCoreApplication::translate("MainWindow", "Tema o asunto de la reunion...", nullptr));
        lblApiKey->setText(QCoreApplication::translate("MainWindow", "  API KEY", nullptr));
        txtApiKey->setPlaceholderText(QCoreApplication::translate("MainWindow", "AIza...", nullptr));
        lblDropHint->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #3a3a3e; font-size: 12px; letter-spacing: 1px;", nullptr));
        lblDropHint->setText(QCoreApplication::translate("MainWindow", "Arrastra un archivo .txt o .docx aqui, o usa el boton", nullptr));
        btnCargarArchivo->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #f0a500; border: 1px solid #f0a500; border-radius: 4px; padding: 8px 20px; font-size: 11px; letter-spacing: 1px; font-weight: bold; } QPushButton:hover { background-color: #f0a500; color: #0e0e0f; }", nullptr));
        btnCargarArchivo->setText(QCoreApplication::translate("MainWindow", "CARGAR ARCHIVO", nullptr));
        txtTranscripcion->setPlaceholderText(QCoreApplication::translate("MainWindow", "La transcripcion aparecera aqui o podes escribirla directamente...", nullptr));
        btnAnalizar->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #f0a500; color: #0e0e0f; border: none; border-radius: 4px; font-size: 13px; font-weight: bold; letter-spacing: 2px; padding: 14px; } QPushButton:hover { background-color: #ffc107; } QPushButton:disabled { background-color: #2a2510; color: #5a5020; }", nullptr));
        btnAnalizar->setText(QCoreApplication::translate("MainWindow", "ANALIZAR CON GEMINI", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTranscripcion), QCoreApplication::translate("MainWindow", "TRANSCRIPCION", nullptr));
        tabResultadosInterno->setStyleSheet(QCoreApplication::translate("MainWindow", "QTabWidget#tabResultadosInterno QTabBar::tab { padding: 8px 22px; font-size: 11px; letter-spacing: 1px; color: #6b6b70; background-color: #141416; border: none; border-bottom: 2px solid transparent; }\n"
"QTabWidget#tabResultadosInterno QTabBar::tab:selected { color: #4ade80; border-bottom: 2px solid #4ade80; }\n"
"QTabWidget#tabResultadosInterno QTabBar::tab:hover:!selected { color: #c8c6c0; }\n"
"QTabWidget#tabResultadosInterno QTabWidget::pane { border: 1px solid #2a2a2e; background-color: #111113; }", nullptr));
        txtResumen->setPlaceholderText(QCoreApplication::translate("MainWindow", "El resumen ejecutivo aparecera aqui despues del analisis...", nullptr));
        tabResultadosInterno->setTabText(tabResultadosInterno->indexOf(subTabResumen), QCoreApplication::translate("MainWindow", "RESUMEN", nullptr));
        txtActa->setPlaceholderText(QCoreApplication::translate("MainWindow", "El acta formal generada aparecera aqui despues del analisis...", nullptr));
        tabResultadosInterno->setTabText(tabResultadosInterno->indexOf(subTabActa), QCoreApplication::translate("MainWindow", "ACTA", nullptr));
        txtTareas->setPlaceholderText(QCoreApplication::translate("MainWindow", "Las tareas por participante apareceran aqui despues del analisis...", nullptr));
        tabResultadosInterno->setTabText(tabResultadosInterno->indexOf(subTabTareas), QCoreApplication::translate("MainWindow", "TAREAS", nullptr));
        btnExportarPDF->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #4ade80; border: 1px solid #4ade80; border-radius: 4px; font-size: 12px; font-weight: bold; letter-spacing: 2px; padding: 14px; } QPushButton:hover { background-color: #4ade80; color: #0e0e0f; } QPushButton:disabled { color: #1a3a1a; border-color: #1a3a1a; }", nullptr));
        btnExportarPDF->setText(QCoreApplication::translate("MainWindow", "EXPORTAR ACTA Y TAREAS COMO PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabResultados), QCoreApplication::translate("MainWindow", "RESULTADOS", nullptr));
        lblTituloHistorial->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #6b6b70; font-size: 11px; letter-spacing: 1px;", nullptr));
        lblTituloHistorial->setText(QCoreApplication::translate("MainWindow", "REUNIONES GUARDADAS EN EL SERVIDOR REMOTO", nullptr));
        btnRefrescarHistorial->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #f0a500; border: 1px solid #f0a500; border-radius: 4px; padding: 6px 14px; font-size: 11px; letter-spacing: 1px; font-weight: bold; } QPushButton:hover { background-color: #f0a500; color: #0e0e0f; }", nullptr));
        btnRefrescarHistorial->setText(QCoreApplication::translate("MainWindow", "REFRESCAR HISTORIAL", nullptr));
        listHistorial->setStyleSheet(QCoreApplication::translate("MainWindow", "QListWidget { background-color: #111113; border: 1px solid #2a2a2e; border-radius: 4px; color: #d8d6d0; padding: 6px; } QListWidget::item { padding: 10px; border-bottom: 1px solid #1a1a1e; border-radius: 4px; } QListWidget::item:selected { background-color: #2a2510; color: #f0a500; border: 1px solid #f0a500; } QListWidget::item:hover:!selected { background-color: #1a1a1e; }", nullptr));
        tabDetalleHistorialInterno->setStyleSheet(QCoreApplication::translate("MainWindow", "QTabWidget#tabDetalleHistorialInterno QTabBar::tab { padding: 8px 22px; font-size: 11px; letter-spacing: 1px; color: #6b6b70; background-color: #141416; border: none; border-bottom: 2px solid transparent; } QTabWidget#tabDetalleHistorialInterno QTabBar::tab:selected { color: #f0a500; border-bottom: 2px solid #f0a500; } QTabWidget#tabDetalleHistorialInterno QTabBar::tab:hover:!selected { color: #c8c6c0; } QTabWidget#tabDetalleHistorialInterno QTabWidget::pane { border: 1px solid #2a2a2e; background-color: #111113; }", nullptr));
        tabDetalleHistorialInterno->setTabText(tabDetalleHistorialInterno->indexOf(subTabHistorialResumen), QCoreApplication::translate("MainWindow", "RESUMEN", nullptr));
        tabDetalleHistorialInterno->setTabText(tabDetalleHistorialInterno->indexOf(subTabHistorialActa), QCoreApplication::translate("MainWindow", "ACTA", nullptr));
        tabDetalleHistorialInterno->setTabText(tabDetalleHistorialInterno->indexOf(subTabHistorialTareas), QCoreApplication::translate("MainWindow", "TAREAS", nullptr));
        btnExportarHistorialPDF->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #4ade80; border: 1px solid #4ade80; border-radius: 4px; font-size: 11px; font-weight: bold; letter-spacing: 1px; padding: 10px; } QPushButton:hover { background-color: #4ade80; color: #0e0e0f; } QPushButton:disabled { color: #1a3a1a; border-color: #1a3a1a; }", nullptr));
        btnExportarHistorialPDF->setText(QCoreApplication::translate("MainWindow", "EXPORTAR REUNI\303\223N SELECCIONADA A PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabHistorial), QCoreApplication::translate("MainWindow", "HISTORIAL", nullptr));
        groupPerfilUsuario->setTitle(QCoreApplication::translate("MainWindow", "INFORMACI\303\223N DE LA CUENTA", nullptr));
        lblPerfilUsuario->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #f0a500; font-size: 16px; font-weight: bold;", nullptr));
        lblPerfilUsuario->setText(QCoreApplication::translate("MainWindow", "Usuario: -", nullptr));
        lblPerfilEstado->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #4ade80; font-size: 12px;", nullptr));
        lblPerfilEstado->setText(QCoreApplication::translate("MainWindow", "\342\227\217 Conectado al servidor remoto (poo.juriserver.website)", nullptr));
        groupPerfilApiKey->setTitle(QCoreApplication::translate("MainWindow", "CONFIGURACI\303\223N DE GEMINI API KEY", nullptr));
        lblPerfilApiKeyHint->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #6b6b70; font-size: 11px;", nullptr));
        lblPerfilApiKeyHint->setText(QCoreApplication::translate("MainWindow", "Pod\303\251s cambiar tu API Key de Google Gemini en cualquier momento. Se guardar\303\241 encriptada en tu cuenta.", nullptr));
        txtPerfilApiKey->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ingres\303\241 la nueva API Key (AIza...)", nullptr));
        btnGuardarApiKey->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #f0a500; color: #0e0e0f; border: none; border-radius: 4px; padding: 8px 18px; font-size: 11px; font-weight: bold; letter-spacing: 1px; } QPushButton:hover { background-color: #ffc107; }", nullptr));
        btnGuardarApiKey->setText(QCoreApplication::translate("MainWindow", "GUARDAR NUEVA API KEY", nullptr));
        lblPerfilApiKeyError->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #f87171; font-size: 11px;", nullptr));
        lblPerfilApiKeyError->setText(QString());
        groupPerfilSesion->setTitle(QCoreApplication::translate("MainWindow", "SESI\303\223N DE USUARIO", nullptr));
        btnCerrarSesion->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: transparent; color: #f87171; border: 1px solid #f87171; border-radius: 4px; font-size: 12px; font-weight: bold; letter-spacing: 1px; padding: 10px; } QPushButton:hover { background-color: #f87171; color: #0e0e0f; }", nullptr));
        btnCerrarSesion->setText(QCoreApplication::translate("MainWindow", "CERRAR SESI\303\223N (LOGOUT)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabPerfil), QCoreApplication::translate("MainWindow", "PERFIL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
