#ifndef ANALIZADORGEMINI_H
#define ANALIZADORGEMINI_H

// =============================================================================
// AnalizadorGemini — Implementacion concreta de AlgoritmoIA para Google Gemini
//
// Hereda de AlgoritmoIA e implementa todos sus metodos virtuales puros.
// Si en el futuro se quiere cambiar a OpenAI, se crea AnalizadorOpenAI
// que hereda de AlgoritmoIA, sin tocar MainWindow ni DataManager.
// Eso es polimorfismo aplicado a proposito real.
// =============================================================================

#include "algoritmoIA.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

class AnalizadorGemini : public AlgoritmoIA
{
    Q_OBJECT

public:
    explicit AnalizadorGemini(QObject *parent = nullptr);

    // Implementacion de metodos virtuales puros de AlgoritmoIA
    QString          nombreProveedor() const override;
    void             analizar(const QString &transcripcion,
                              const QString &tema,
                              const QString &apiKey) override;
    QString          construirPrompt(const QString &transcripcion,
                                     const QString &tema) const override;
    ResultadoAnalisis parsearRespuesta(const QString &respuestaCruda) const override;

private slots:
    void onRespuestaRecibida(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;

    // Modelo y endpoint de Gemini
    static const QString MODELO;
    static const QString ENDPOINT_BASE;
};

#endif // ANALIZADORGEMINI_H
