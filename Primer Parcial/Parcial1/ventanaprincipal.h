#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QWidget>
#include "dibujo.h"

namespace Ui  {
class VentanaPrincipal;
}

class VentanaPrincipal : public QWidget  {
    Q_OBJECT

public:
    VentanaPrincipal( QWidget * parent = nullptr );
    ~VentanaPrincipal();

public slots:
    // Recibe el usuario validado desde Login
    void slot_setUsuario( QString usuario );

private slots:
    void slot_guardarDibujo();
    void slot_limpiar();
    void slot_exportarImagen();
    void slot_tipoCambiado( int index );
    void slot_dibujoModificado();

private:
    Ui::VentanaPrincipal * ui;
    QString m_usuarioActual;
    Dibujo * m_dibujoActual;

    // Crea un nuevo Dibujo del tipo indicado, preservando trazos existentes
    void crearDibujo( int tipo );
};

#endif // VENTANAPRINCIPAL_H
