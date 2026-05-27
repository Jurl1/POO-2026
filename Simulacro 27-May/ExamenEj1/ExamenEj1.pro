QT += core gui widgets network sql

CONFIG += c++17

TARGET = ExamenEj1

SOURCES += \
    main.cpp \
    login.cpp \
    imagen.cpp \
    admindb.cpp \
    ventanaprincipal.cpp

HEADERS += \
    login.h \
    imagen.h \
    admindb.h \
    ventanaprincipal.h

FORMS += \
    login.ui
