#include <QDebug>
#include <QCoreApplication>

class CuentaBancaria  {
private:
    int saldo;

    // compararSaldo puede acceder al atributo privado 'saldo'
    friend bool compararSaldo( CuentaBancaria, CuentaBancaria );

public:
    CuentaBancaria( int saldoInicial ) : saldo( saldoInicial )  {  }

    void depositar( int monto )  {
        saldo += monto;
    }

    void mostrar()  {
        qDebug() << "Saldo:" << saldo;
    }
};

// Función amiga: NO es miembro de CuentaBancaria, pero accede a 'saldo'
bool compararSaldo( CuentaBancaria c1, CuentaBancaria c2 )  {
    return c1.saldo > c2.saldo;
}

int main( int argc, char ** argv )  {
    QCoreApplication a( argc, argv );

    CuentaBancaria cuenta1( 1000 );
    CuentaBancaria cuenta2( 500 );

    qDebug() << "--- Cuentas iniciales ---";
    qDebug() << "Cuenta 1:";
    cuenta1.mostrar();
    qDebug() << "Cuenta 2:";
    cuenta2.mostrar();

    cuenta1.depositar( 200 );
    cuenta2.depositar( 900 );

    qDebug() << "\n--- Cuentas tras depósitos ---";
    qDebug() << "Cuenta 1:";
    cuenta1.mostrar();
    qDebug() << "Cuenta 2:";
    cuenta2.mostrar();

    qDebug() << "\n--- Comparación ---";
    if ( compararSaldo( cuenta1, cuenta2 ) )
        qDebug() << "Cuenta 1 tiene mayor saldo que Cuenta 2.";
    else
        qDebug() << "Cuenta 2 tiene mayor o igual saldo que Cuenta 1.";

    return 0;
}
