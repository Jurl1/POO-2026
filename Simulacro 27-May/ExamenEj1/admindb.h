#ifndef ADMINDB_H
#define ADMINDB_H

#include <QSqlDatabase>
#include <QString>

class AdminDB  {

private:
    static AdminDB * instancia;
    AdminDB();

    QSqlDatabase db;

public:
    static AdminDB * getInstancia();

    void conectar();
    bool validarUsuario( const QString & usuario, const QString & clave );
    void registrarLogin( const QString & usuario );
};

#endif // ADMINDB_H
