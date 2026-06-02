#include <QApplication>
#include <QElapsedTimer>
#include <QDebug>

#include "sensor.h"

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    Sensor sensor;
    const int ITERACIONES = 10000000;  // 10 millones
    volatile int    resultadoInt = 0;
    volatile double resultadoDouble = 0;

    QElapsedTimer timer;

    // --- getValorBruto (inline implícito) ---
    timer.start();
    for ( int i = 0; i < ITERACIONES; i++ )  {
        resultadoInt = sensor.getValorBruto();
    }
    qDebug() << "getValorBruto (inline):" << timer.nsecsElapsed() / 1000000.0 << "ms";

    // --- getValorBrutoOffline ---
    timer.start();
    for ( int i = 0; i < ITERACIONES; i++ )  {
        resultadoInt = sensor.getValorBrutoOffline();
    }
    qDebug() << "getValorBrutoOffline:  " << timer.nsecsElapsed() / 1000000.0 << "ms";

    // --- getValorNormalizado (inline explícito) ---
    timer.start();
    for ( int i = 0; i < ITERACIONES; i++ )  {
        resultadoDouble = sensor.getValorNormalizado();
    }
    qDebug() << "getValorNormalizado (inline):" << timer.nsecsElapsed() / 1000000.0 << "ms";

    // --- getValorNormalizadoOffline ---
    timer.start();
    for ( int i = 0; i < ITERACIONES; i++ )  {
        resultadoDouble = sensor.getValorNormalizadoOffline();
    }
    qDebug() << "getValorNormalizadoOffline:  " << timer.nsecsElapsed() / 1000000.0 << "ms";

    // Evitar warning de variable no usada
    Q_UNUSED( resultadoInt )
    Q_UNUSED( resultadoDouble )

    return 0;
}
