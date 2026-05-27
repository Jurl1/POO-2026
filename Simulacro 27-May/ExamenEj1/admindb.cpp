#include "admindb.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStringList>

AdminDB * AdminDB::instancia = nullptr;

AdminDB::AdminDB()  {
}

AdminDB * AdminDB::getInstancia()  {
    if ( instancia == nullptr )  {
        instancia = new AdminDB;
    }
    return instancia;
}

void AdminDB::conectar()  {
    db = QSqlDatabase::addDatabase( "QSQLITE" );

    // Buscar la base de datos en distintas rutas relativas (depende del working directory)
    QStringList rutas;
    rutas << "../../login.sqlite"
          << "../../../login.sqlite"
          << "../login.sqlite"
          << "login.sqlite";

    QString rutaEncontrada;

    for ( int i = 0; i < rutas.size(); i++ )  {
        if ( QFile::exists( rutas.at( i ) ) )  {
            rutaEncontrada = rutas.at( i );
            break;
        }
    }

    if ( rutaEncontrada.isEmpty() )  {
        qDebug() << "No se encontró login.sqlite en ninguna ruta relativa.";
        qDebug() << "Directorio actual:" << QDir::currentPath();
        return;
    }

    qDebug() << "Base de datos encontrada en:" << QDir( rutaEncontrada ).absolutePath();

    db.setDatabaseName( rutaEncontrada );

    if ( ! db.open() )  {
        qDebug() << "Error al conectar la base de datos:" << db.lastError().text();
        return;
    }

    qDebug() << "Base de datos conectada.";
}

bool AdminDB::validarUsuario( const QString & usuario, const QString & clave )  {
    QSqlQuery query;
    query.prepare( "SELECT id FROM usuarios WHERE usuario = :u AND clave = :c" );
    query.bindValue( ":u", usuario );
    query.bindValue( ":c", clave );
    query.exec();
    return query.next();
}

void AdminDB::registrarLogin( const QString & usuario )  {
    QString fechaHora = QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" );

    QSqlQuery query;
    query.prepare( "UPDATE usuarios SET fecha_login = :f WHERE usuario = :u" );
    query.bindValue( ":f", fechaHora );
    query.bindValue( ":u", usuario );

    if ( query.exec() )  {
        qDebug() << "Login registrado para:" << usuario << "en" << fechaHora;
    }
}
