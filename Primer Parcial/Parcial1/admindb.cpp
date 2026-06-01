#include "admindb.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfo>
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

// Busca la base de datos en varias rutas relativas para adaptarse
// al directorio de trabajo de Qt Creator sin usar rutas absolutas.
bool AdminDB::conectar()  {
    db = QSqlDatabase::addDatabase( "QSQLITE" );

    QStringList rutas;
    rutas << "../../../dibujos.sqlite"
          << "../../dibujos.sqlite"
          << "../dibujos.sqlite"
          << "dibujos.sqlite";

    QString rutaEncontrada;

    for ( int i = 0; i < rutas.size(); i++ )  {
        if ( QFile::exists( rutas.at( i ) ) )  {
            rutaEncontrada = rutas.at( i );
            break;
        }
    }

    if ( rutaEncontrada.isEmpty() )  {
        qDebug() << "No se encontró dibujos.sqlite. Directorio actual:" << QDir::currentPath();
        return false;
    }

    qDebug() << "Base de datos encontrada en:" << QFileInfo( rutaEncontrada ).absoluteFilePath();
    db.setDatabaseName( rutaEncontrada );

    if ( ! db.open() )  {
        qDebug() << "Error al abrir la base de datos:" << db.lastError().text();
        return false;
    }

    qDebug() << "Base de datos conectada correctamente.";
    return true;
}

// Valida credenciales contra la tabla usuarios
bool AdminDB::validarUsuario( const QString & usuario, const QString & clave )  {
    QSqlQuery query;
    query.prepare( "SELECT id FROM usuarios WHERE usuario = :u AND clave = :c" );
    query.bindValue( ":u", usuario );
    query.bindValue( ":c", clave );

    if ( ! query.exec() )  {
        qDebug() << "Error en consulta SQL:" << query.lastError().text();
        return false;
    }

    return query.next();
}

// Registra el ingreso del usuario en la tabla log_sesiones (historial)
// y actualiza la fecha del último login en la tabla usuarios.
void AdminDB::registrarLogin( const QString & usuario )  {
    QString fechaHora = QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" );

    // INSERT en log_sesiones: queda el historial completo de ingresos
    QSqlQuery queryLog;
    queryLog.prepare( "INSERT INTO log_sesiones (usuario, fecha) VALUES (:u, :f)" );
    queryLog.bindValue( ":u", usuario );
    queryLog.bindValue( ":f", fechaHora );

    if ( queryLog.exec() )  {
        qDebug() << "Login registrado en log_sesiones:" << usuario << fechaHora;
    }
    else  {
        qDebug() << "Error al registrar en log_sesiones:" << queryLog.lastError().text();
    }

    // UPDATE en usuarios: actualiza la fecha del último ingreso
    QSqlQuery queryUpdate;
    queryUpdate.prepare( "UPDATE usuarios SET fecha_login = :f WHERE usuario = :u" );
    queryUpdate.bindValue( ":f", fechaHora );
    queryUpdate.bindValue( ":u", usuario );
    queryUpdate.exec();
}

// Inserta un nuevo registro en la tabla dibujos
bool AdminDB::guardarDibujo( const QString & nombre, const QString & categoria,
                              const QString & tipo, const QString & usuario )  {
    QString fechaHora = QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" );

    QSqlQuery query;
    query.prepare( "INSERT INTO dibujos (nombre, categoria, tipo, fecha, usuario) "
                   "VALUES (:n, :c, :t, :f, :u)" );
    query.bindValue( ":n", nombre );
    query.bindValue( ":c", categoria );
    query.bindValue( ":t", tipo );
    query.bindValue( ":f", fechaHora );
    query.bindValue( ":u", usuario );

    if ( ! query.exec() )  {
        qDebug() << "Error al guardar dibujo:" << query.lastError().text();
        return false;
    }

    qDebug() << "Dibujo guardado:" << nombre << "-" << tipo << "-" << usuario;
    return true;
}
