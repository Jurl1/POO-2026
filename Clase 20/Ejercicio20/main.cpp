#include <QApplication>
#include <QDebug>
#include <vector>

#include "instrumento.h"
#include "guitarra.h"
#include "bateria.h"
#include "teclado.h"

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    std::vector< Instrumento * > instrumentos;

    instrumentos.push_back( new Guitarra );
    instrumentos.push_back( new Guitarra( 7, "Fender" ) );
    instrumentos.push_back( new Bateria );
    instrumentos.push_back( new Teclado );
    instrumentos.push_back( new Teclado( 88, "Casio", 110 ) );

    qDebug() << "=== Recorriendo el vector de instrumentos ===";
    qDebug();

    for ( unsigned int i = 0; i < instrumentos.size(); i++ )  {
        instrumentos.at( i )->verlo();
        instrumentos.at( i )->sonar();
        qDebug();
    }

    qDebug() << "=== Eliminando instrumentos ===";
    qDebug();

    for ( unsigned int i = 0; i < instrumentos.size(); i++ )  {
        delete instrumentos.at( i );
    }

    return 0;
}
