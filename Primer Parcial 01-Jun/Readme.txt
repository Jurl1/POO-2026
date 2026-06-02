Instrucciones generales

    Los ejercicios deben resolverse utilizando C++ con la biblioteca Qt.
    La clase base principal debe ser QWidget. No se permite el uso de QMainWindow.
    Se debe utilizar SIGNAL() y SLOT() explícitamente para conectar señales y slots.
    No se permite el uso de lambdas ni punteros a funciones en connect(...).
    No se debe usar QPixmap. Usar exclusivamente QImage.
    No se deben usar rutas absolutas.

Estado del examen: Activo
Ventana: 6/1/2026, 3:30:00 PM - 6/1/2026, 5:15:00 PM | Intentos maximos: 1
Ejercicio 1: Gestor de dibujos
Ejercicio – Gestor de dibujos con login, categorías y persistencia

Objetivo:
Desarrollar una aplicación en C++ y Qt que permita iniciar sesión, crear dibujos simples con el mouse, clasificarlos por tipo y guardar información en una base de datos SQLite.
Requisitos

Crear una aplicación Qt Widgets con las siguientes partes:
1. Login

Implementar una clase Login usando Qt Designer, en los archivos:

    login.h
    login.cpp
    login.ui

Debe contener:

    Un QLineEdit para usuario.
    Un QLineEdit para clave.
    Un botón Iniciar sesión.

La validación debe realizarse contra una base de datos SQLite usando una clase AdminDB.

La tabla usuarios debe permitir validar al menos el usuario:

    usuario: admin
    clave: 1234

Al iniciar sesión correctamente:

    Se debe ocultar el login.
    Se debe mostrar una ventana principal.
    Se debe registrar en la base de datos o en un archivo de log el usuario y la fecha/hora del ingreso.

2. Clase abstracta para dibujos

Diseñar una clase abstracta Dibujo con al menos:

    Nombre del dibujo.
    Categoría o etiqueta.
    Método virtual puro dibujar( QPainter * painter ).
    Método virtual descripcion() que devuelva un texto descriptivo.

Implementar al menos dos clases derivadas:

    DibujoLibre: representa un dibujo realizado con el mouse.
    DibujoConMarco: representa un dibujo realizado con el mouse, pero además dibuja un marco alrededor.

Debe usarse polimorfismo mediante punteros o referencias a la clase base Dibujo.
3. Widget personalizado de dibujo

Crear una clase Lienzo que herede de QWidget.

Debe:

    Estar promocionada dentro de la interfaz usando Qt Designer.
    Redefinir paintEvent.
    Redefinir eventos de mouse para permitir dibujar a mano alzada.
    Usar QPainter.
    Emitir una señal propia cuando el dibujo sea modificado.

Ejemplo de señal:

signals:
    void signal_dibujoModificado();

4. Ventana principal

Crear una clase VentanaPrincipal usando Qt Designer.

Debe contener:

    El widget personalizado Lienzo.
    Un QLineEdit para ingresar el nombre del dibujo.
    Un QLineEdit o QComboBox para la categoría.
    Una opción para elegir si el dibujo será DibujoLibre o DibujoConMarco.
    Botón Guardar dibujo.
    Botón Limpiar.
    Botón Exportar imagen.

La organización visual debe usar layouts.
5. Persistencia

Al presionar Guardar dibujo, se debe almacenar en SQLite:

    Nombre del dibujo.
    Categoría.
    Tipo de dibujo.
    Fecha y hora.
    Usuario que inició sesión.

No es obligatorio guardar todas las coordenadas del dibujo, pero sí debe quedar registrado el dibujo creado.
6. Exportación

El botón Exportar imagen debe permitir guardar el contenido del lienzo como imagen .jpg o .png.

Se debe usar QFileDialog.
7. Condiciones obligatorias

El proyecto debe incluir obligatoriamente:

    Clases propias separadas en .h y .cpp.
    Herencia.
    Polimorfismo.
    Al menos una clase abstracta.
    Al menos un método virtual puro.
    Uso de paintEvent.
    Uso de eventos de mouse.
    Uso de signals y slots.
    Uso de SQLite mediante una clase AdminDB.
    Uso de Qt Designer.
    Al menos un widget promocionado.

Archivos obligatorios: main.cpp, login.h, login.cpp, login.ui, admindb.h, admindb.cpp, lienzo.h, lienzo.cpp, dibujo.h
Archivos prohibidos: *.exe, *.dll, *pro.user*, /build, Makefile