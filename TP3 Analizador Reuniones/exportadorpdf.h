#ifndef EXPORTADORPDF_H
#define EXPORTADORPDF_H

#include <QString>
#include "analizador.h"

class ExportadorPDF
{
public:
    // Abre un diálogo para elegir destino y exporta el acta + tareas
    // Retorna true si se exportó correctamente
    static bool exportar(const QString &tema,
                         const ResultadoAnalisis &resultado,
                         QWidget *parent = nullptr);
};

#endif // EXPORTADORPDF_H
