QT += widgets core gui sql

CONFIG += c++17

SOURCES += \
    bienvenida.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    bienvenida.h \
    widget.h

FORMS += \
    bienvenida.ui \
    widget.ui

# -----------------------------------------------------------
# Copia la base de datos al directorio de salida del build
# automáticamente cada vez que compilás.
# Así el ejecutable siempre encuentra la DB actualizada.
# -----------------------------------------------------------
DB_SOURCE = $$PWD/base_de_datos_POO.db
DB_DEST   = $$OUT_PWD/base_de_datos_POO.db

copydb.commands = $${QMAKE_COPY} \"$$shell_path($$DB_SOURCE)\" \"$$shell_path($$DB_DEST)\"
first.depends = $(first) copydb
export(first.depends)
export(copydb.commands)
QMAKE_EXTRA_TARGETS += first copydb

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target