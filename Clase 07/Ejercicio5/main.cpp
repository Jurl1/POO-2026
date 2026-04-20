#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel *label = new QLabel;

    // Cambia la ruta por la ubicación real de tu imagen en el disco duro.
    // En Windows recuerda usar barras dobles \\ o barras normales / (ej. "C:/imagenes/foto.jpg")
    QPixmap pixmap("ruta/a/tu/imagen_alta_resolucion.jpg");

    if (pixmap.isNull()) {
        label->setText("No se pudo cargar la imagen. Revisa la ruta.");
    } else {
        // Escalar la imagen a la resolución de la pantalla principal sin deformar (KeepAspectRatio)
        // Usamos SmoothTransformation para mantener la calidad
        label->setPixmap(pixmap.scaled(app.primaryScreen()->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation));

        // Centrar la imagen en el QLabel
        label->setAlignment(Qt::AlignCenter);
    }

    // Mostrar maximizado
    label->showMaximized();

    // Configurar el QTimer para cerrar la aplicación después de 3000 ms (3 segundos)
    QTimer::singleShot(3000, &app, &QApplication::quit);

    return app.exec();
}