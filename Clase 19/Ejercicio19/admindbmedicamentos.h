#ifndef ADMINDBMEDICAMENTOS_H
#define ADMINDBMEDICAMENTOS_H

#include <QSqlDatabase>
#include <QList>
#include "cajamedicamento.h"

class AdminDBMedicamentos  {

private:
    static AdminDBMedicamentos * instancia;
    AdminDBMedicamentos();

    QSqlDatabase db;

public:
    static AdminDBMedicamentos * getInstancia();

    void conectar();
    bool insertarCaja( float dosis );
    QList< CajaMedicamento > obtenerTodas();
    float obtenerTotalDosis();
};

#endif // ADMINDBMEDICAMENTOS_H
