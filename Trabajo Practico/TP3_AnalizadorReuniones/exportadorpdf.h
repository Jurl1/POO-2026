#ifndef EXPORTADORPDF_H
#define EXPORTADORPDF_H

// =============================================================================
// ExportadorPDF — Responsabilidad unica: exportar resultados a PDF
//
// Clase separada de AlgoritmoIA y de MainWindow intencionalmente:
// la logica de exportacion no es IA ni es visualizacion.
// =============================================================================

#include "algoritmoIA.h"
#include <QWidget>

class ExportadorPDF
{
public:
    // Exporta acta + tareas a un PDF elegido por el usuario
    // Retorna true si se exporto correctamente
    static bool exportar(const QString &tema,
                         const ResultadoAnalisis &resultado,
                         QWidget *parent = nullptr);

private:
    // Construye el HTML interno del documento
    static QString construirHTML(const QString &tema,
                                  const ResultadoAnalisis &resultado);
};

#endif // EXPORTADORPDF_H
