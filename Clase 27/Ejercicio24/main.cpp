#include <QCoreApplication>
#include <QDebug>
#include <QString>

class Persona  {
private:
    QString nombre;
    static int contador;  // Miembro estático: compartido por todas las instancias

public:
    Persona( const QString & nombre ) : nombre( nombre )  {
        contador++;  // Se incrementa cada vez que se crea una Persona
    }

    void mostrar()  {
        qDebug() << "Nombre:" << nombre;
    }

    // Método estático: accede solo al miembro estático 'contador'
    static int totalPersonas()  {
        return contador;
    }
};

// Definición del miembro estático fuera de la clase
int Persona::contador = 0;

int main( int argc, char ** argv )  {
    QCoreApplication a( argc, argv );

    qDebug() << "Personas creadas:" << Persona::totalPersonas();

    Persona p1( "Ana" );
    Persona p2( "Carlos" );
    Persona p3( "Lucía" );

    p1.mostrar();
    p2.mostrar();
    p3.mostrar();

    qDebug() << "Personas creadas:" << Persona::totalPersonas();

    Persona p4( "Martín" );
    p4.mostrar();

    qDebug() << "Personas creadas:" << Persona::totalPersonas();

    return 0;
}
