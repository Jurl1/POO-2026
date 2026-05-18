QT += core gui widgets network printsupport

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    algoritmoIA.cpp \
    analizadorgemini.cpp \
    datamanager.cpp \
    exportadorpdf.cpp

HEADERS += \
    mainwindow.h \
    algoritmoIA.h \
    analizadorgemini.h \
    datamanager.h \
    exportadorpdf.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
