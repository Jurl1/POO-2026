#include "admindbmedicamentos.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AdminDBMedicamentos * AdminDBMedicamentos::instancia = nullptr;

AdminDBMedicamentos::AdminDBMedicamentos()  {
}

AdminDBMedicamentos * AdminDBMedicamentos::getInstancia()  {
    if ( instancia == nullptr )  {
        instancia = new AdminDBMedicamentos;
    }
    return instancia;
}

void AdminDBMedicamentos::conectar()  {
    db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "medicamentos.sqlite" );

    if ( ! db.open() )  {
        qDebug() << "Error al conectar la base de datos:" << db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.exec( "CREATE TABLE IF NOT EXISTS cajas_medicamentos ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "dosis_totales REAL NOT NULL)" );

    qDebug() << "Base de datos conectada correctamente.";
}

bool AdminDBMedicamentos::insertarCaja( float dosis )  {
    float totalActual = obtenerTotalDosis();

    if ( totalActual + dosis > 1000 )  {
        return false;
    }

    QSqlQuery query;
    query.prepare( "INSERT INTO cajas_medicamentos ( dosis_totales ) VALUES ( :dosis )" );
    query.bindValue( ":dosis", dosis );

    return query.exec();
}

QList< CajaMedicamento > AdminDBMedicamentos::obtenerTodas()  {
    QList< CajaMedicamento > lista;

    QSqlQuery query;
    query.exec( "SELECT id, dosis_totales FROM cajas_medicamentos" );

    while ( query.next() )  {
        int id = query.value( 0 ).toInt();
        float dosis = query.value( 1 ).toFloat();
        lista.append( CajaMedicamento( id, dosis ) );
    }

    return lista;
}

float AdminDBMedicamentos::obtenerTotalDosis()  {
    QSqlQuery query;
    query.exec( "SELECT SUM( dosis_totales ) FROM cajas_medicamentos" );

    if ( query.next() )  {
        return query.value( 0 ).toFloat();
    }

    return 0;
}
