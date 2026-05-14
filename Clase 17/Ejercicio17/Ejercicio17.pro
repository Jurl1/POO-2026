QT += widgets

CONFIG += c++17

SOURCES += \
    boton.cpp \
    main.cpp \
    ventana.cpp

HEADERS += \
    boton.h \
    ventana.h

FORMS += \
    boton.ui \
    ventana.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
