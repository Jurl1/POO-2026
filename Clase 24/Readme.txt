Ejercicio 22:
Inline en acción — Simulador de Sensor Inteligente

Implementar una clase que simule un sensor, aplicando funciones frecuentes tanto en versión inline como offline, y luego comparar el rendimiento al ejecutar esas funciones millones de veces.
Parte 1: Diseño de la clase Sensor

Implementar una clase Sensor con las siguientes características:

Atributos:

    int valorActual → puede inicializarse con un valor aleatorio entre 0 y 1023.

Métodos:

    int getValorBruto() → devuelve el valor actual sin modificar. Definir dentro de la clase (será inline implícito).
    int getValorBrutoOffline() → igual que el anterior, pero definir fuera de la clase sin usar inline (será una función normal).
    double getValorNormalizado() → devuelve valorActual / 1023.0. Definir como inline explícito.
    double getValorNormalizadoOffline() → igual que el anterior, pero sin inline.

Parte 2: Benchmark de rendimiento (Prueba de rendimiento)

Utilizar QElapsedTimer para medir el tiempo de ejecución de:

    Ejecutar 10 millones de veces la llamada a getValorBruto().
    Ejecutar 10 millones de veces la llamada a getValorBrutoOffline().
    Ejecutar 10 millones de veces la llamada a getValorNormalizado().
    Ejecutar 10 millones de veces la llamada a getValorNormalizadoOffline().

Mostrar los tiempos en consola con qDebug().