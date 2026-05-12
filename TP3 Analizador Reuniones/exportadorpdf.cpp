#include "exportadorpdf.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include <QPrinter>
#include <QDateTime>
#include <QWidget>

bool ExportadorPDF::exportar(const QString &tema,
                              const ResultadoAnalisis &resultado,
                              QWidget *parent)
{
    QString ruta = QFileDialog::getSaveFileName(
        parent,
        "Exportar acta como PDF",
        "acta_reunion.pdf",
        "PDF (*.pdf)"
    );

    if (ruta.isEmpty()) return false;

    // Construir el HTML del documento
    QString fechaHoy = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm");
    QString participantes = resultado.participantes.join(", ");
    if (participantes.isEmpty()) participantes = "No detectados";

    // Escapar el contenido para HTML
    auto esc = [](const QString &s) {
        QString r = s;
        r.replace("&", "&amp;");
        r.replace("<", "&lt;");
        r.replace(">", "&gt;");
        r.replace("\n", "<br>");
        return r;
    };

    // Formatear tareas: resaltar el nombre del participante
    QString tareasHtml;
    QString tareasRaw = resultado.tareasPorParticipante;
    for (const QString &linea : tareasRaw.split("\n")) {
        if (linea.startsWith("▶")) {
            tareasHtml += "<p style='margin:8px 0 2px 0;'><b>" + esc(linea) + "</b></p>";
        } else if (linea.startsWith("  •")) {
            tareasHtml += "<p style='margin:0 0 0 20px;'>" + esc(linea) + "</p>";
        } else if (!linea.trimmed().isEmpty()) {
            tareasHtml += "<p>" + esc(linea) + "</p>";
        }
    }

    QString html = QString(R"(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<style>
  body { font-family: Arial, sans-serif; font-size: 11pt; color: #1a1a1a; margin: 40px; }
  h1 { font-size: 18pt; color: #1a3a6b; border-bottom: 2px solid #1a3a6b; padding-bottom: 6px; }
  h2 { font-size: 13pt; color: #2c5282; margin-top: 24px; border-bottom: 1px solid #bee3f8; padding-bottom: 4px; }
  .meta { color: #555; font-size: 10pt; margin-bottom: 20px; }
  .box { background: #f7fafc; border-left: 4px solid #3182ce; padding: 12px 16px; margin: 8px 0; }
  .acta { white-space: pre-wrap; line-height: 1.6; }
  .footer { margin-top: 40px; font-size: 9pt; color: #999; border-top: 1px solid #eee; padding-top: 8px; }
</style>
</head>
<body>

<h1>Acta de Reunión</h1>
<div class="meta">
  <b>Tema:</b> %1 &nbsp;&nbsp;|&nbsp;&nbsp;
  <b>Fecha de análisis:</b> %2 &nbsp;&nbsp;|&nbsp;&nbsp;
  <b>Participantes:</b> %3
</div>

<h2>Resumen Ejecutivo</h2>
<div class="box">%4</div>

<h2>Acta Completa</h2>
<div class="acta">%5</div>

<h2>Tareas por Participante</h2>
%6

<div class="footer">Generado automáticamente por Analizador de Reuniones — %2</div>
</body>
</html>
)").arg(
        esc(tema),
        fechaHoy,
        esc(participantes),
        esc(resultado.resumenEjecutivo),
        esc(resultado.acta),
        tareasHtml
    );

    // Renderizar y exportar como PDF
    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(ruta);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);

    doc.print(&printer);

    QMessageBox::information(parent, "PDF exportado",
                             "El acta fue exportada correctamente en:\n" + ruta);
    return true;
}
