#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

// Resultado del análisis devuelto por OpenAI
struct ResultadoAnalisis {
    QString resumenEjecutivo;
    QString acta;
    QString tareasPorParticipante; // Texto formateado con tareas
    QStringList participantes;
};

class Analizador : public QObject
{
    Q_OBJECT

public:
    explicit Analizador(QObject *parent = nullptr);

    // Llama a Gemini con la transcripción y el tema
    void analizar(const QString &transcripcion, const QString &tema, const QString &apiKey);

signals:
    void analisisCompleto(const ResultadoAnalisis &resultado);
    void error(const QString &mensaje);
    void progreso(const QString &mensaje);

private slots:
    void onRespuestaRecibida(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
    QString construirPrompt(const QString &transcripcion, const QString &tema) const;
    ResultadoAnalisis parsearRespuesta(const QString &json) const;
};

#endif // ANALIZADOR_H
