QT += core gui widgets network printsupport

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    analizador.cpp \
    exportadorpdf.cpp

HEADERS += \
    mainwindow.h \
    analizador.h \
    exportadorpdf.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
