QT += core gui widgets sql

CONFIG += c++17

TARGET = Parcial1

SOURCES += \
    main.cpp \
    login.cpp \
    admindb.cpp \
    dibujo.cpp \
    dibujolibre.cpp \
    dibujoconmarco.cpp \
    lienzo.cpp \
    ventanaprincipal.cpp

HEADERS += \
    login.h \
    admindb.h \
    dibujo.h \
    dibujolibre.h \
    dibujoconmarco.h \
    lienzo.h \
    ventanaprincipal.h

FORMS += \
    login.ui \
    ventanaprincipal.ui
