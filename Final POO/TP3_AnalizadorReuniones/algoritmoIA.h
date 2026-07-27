#ifndef ALGORITMOIA_H
#define ALGORITMOIA_H

// =============================================================================
// AlgoritmoIA — Clase abstracta base para motores de inteligencia artificial
//
// Define la interfaz que cualquier motor de IA debe implementar.
// Usa metodos virtuales puros para forzar la implementacion en clases derivadas.
// Esto permite polimorfismo: MainWindow trabaja con AlgoritmoIA* sin saber
// si adentro hay Gemini, OpenAI, u otro proveedor.
// =============================================================================

#include <QObject>
#include <QStringList>

// Estructura que contiene el resultado del analisis de una reunion
struct ResultadoAnalisis {
    QString      resumenEjecutivo;
    QString      acta;
    QString      tareasPorParticipante;
    QStringList  participantes;
    bool         valido = false;  // false si hubo error o no se proceso aun
};

class AlgoritmoIA : public QObject
{
    Q_OBJECT

public:
    explicit AlgoritmoIA(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~AlgoritmoIA() {}

    // ---------------------------------------------------------
    // Metodos virtuales puros: toda clase derivada DEBE definirlos
    // ---------------------------------------------------------

    // Nombre del proveedor (ej: "Gemini 2.5 Flash", "OpenAI GPT-4o")
    virtual QString nombreProveedor() const = 0;

    // Ejecuta el analisis. Emite analisisCompleto o error cuando termina.
    virtual void analizar(const QString &transcripcion,
                          const QString &tema,
                          const QString &apiKey) = 0;

    // Construye el prompt que se envia al modelo
    virtual QString construirPrompt(const QString &transcripcion,
                                    const QString &tema) const = 0;

    // Parsea la respuesta cruda del modelo y devuelve un ResultadoAnalisis
    virtual ResultadoAnalisis parsearRespuesta(const QString &respuestaCruda) const = 0;

signals:
    void analisisCompleto(const ResultadoAnalisis &resultado);
    void error(const QString &mensaje);
    void progreso(const QString &mensaje);
};

#endif // ALGORITMOIA_H
