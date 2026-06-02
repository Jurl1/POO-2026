#ifndef ADMINDB_H
#define ADMINDB_H

#include <QSqlDatabase>
#include <QString>

// Clase Singleton para gestionar la base de datos SQLite.
// Maneja la conexión, validación de usuarios y persistencia de dibujos.
class AdminDB  {

private:
    static AdminDB * instancia;
    AdminDB();
    AdminDB( const AdminDB & ) = delete;
    AdminDB & operator=( const AdminDB & ) = delete;

    QSqlDatabase db;

public:
    static AdminDB * getInstancia();

    // Conecta a la base de datos buscando el archivo en rutas relativas
    bool conectar();

    // Valida usuario y clave contra la tabla usuarios
    bool validarUsuario( const QString & usuario, const QString & clave );

    // Registra la fecha/hora del login en la tabla usuarios
    void registrarLogin( const QString & usuario );

    // Guarda los metadatos de un dibujo creado
    bool guardarDibujo( const QString & nombre, const QString & categoria,
                        const QString & tipo, const QString & usuario );
};

#endif // ADMINDB_H
