#include "exportadorpdf.h"
#include "datamanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDocument>
#include <QPrinter>
#include <QDateTime>

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

    QString html = construirHTML(tema, resultado);

    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(ruta);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);

    doc.print(&printer);

    QMessageBox::information(parent, "PDF exportado",
        QString("Acta exportada correctamente.\nArchivo: %1\n\n"
                "Analisis realizados en esta sesion: %2")
            .arg(ruta)
            .arg(DataManager::instancia().cantidadAnalisis()));

    return true;
}

QString ExportadorPDF::construirHTML(const QString &tema,
                                      const ResultadoAnalisis &resultado)
{
    QString fechaHoy     = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm");
    QString participantes = resultado.participantes.join(", ");
    if (participantes.isEmpty()) participantes = "No detectados";

    // Funcion lambda para escapar HTML
    auto esc = [](const QString &s) {
        QString r = s;
        r.replace("&", "&amp;");
        r.replace("<", "&lt;");
        r.replace(">", "&gt;");
        r.replace("\n", "<br>");
        return r;
    };

    // Formatear tareas con HTML
    QString tareasHtml;
    for (const QString &linea : resultado.tareasPorParticipante.split("\n")) {
        if (linea.startsWith(">")) {
            tareasHtml += "<p style='margin:8px 0 2px 0;'><b>" + esc(linea) + "</b></p>";
        } else if (linea.startsWith("  *")) {
            tareasHtml += "<p style='margin:0 0 0 20px;'>" + esc(linea) + "</p>";
        } else if (!linea.trimmed().isEmpty()) {
            tareasHtml += "<p>" + esc(linea) + "</p>";
        }
    }

    return QString(R"(
<!DOCTYPE html>
<html>
<head><meta charset="UTF-8">
<style>
  body { font-family: Arial, sans-serif; font-size: 11pt; color: #1a1a1a; margin: 40px; }
  h1   { font-size: 18pt; color: #1a3a6b; border-bottom: 2px solid #1a3a6b; padding-bottom: 6px; }
  h2   { font-size: 13pt; color: #2c5282; margin-top: 24px; border-bottom: 1px solid #bee3f8; padding-bottom: 4px; }
  .meta   { color: #555; font-size: 10pt; margin-bottom: 20px; }
  .box    { background: #f7fafc; border-left: 4px solid #3182ce; padding: 12px 16px; margin: 8px 0; }
  .acta   { white-space: pre-wrap; line-height: 1.6; }
  .footer { margin-top: 40px; font-size: 9pt; color: #999; border-top: 1px solid #eee; padding-top: 8px; }
</style>
</head>
<body>
<h1>Acta de Reunion</h1>
<div class="meta">
  <b>Tema:</b> %1 &nbsp;|&nbsp;
  <b>Fecha:</b> %2 &nbsp;|&nbsp;
  <b>Participantes:</b> %3
</div>
<h2>Resumen Ejecutivo</h2>
<div class="box">%4</div>
<h2>Acta Completa</h2>
<div class="acta">%5</div>
<h2>Tareas por Participante</h2>
%6
<div class="footer">Generado por Analizador de Reuniones — %2</div>
</body></html>
)").arg(esc(tema), fechaHoy, esc(participantes),
        esc(resultado.resumenEjecutivo),
        esc(resultado.acta),
        tareasHtml);
}
