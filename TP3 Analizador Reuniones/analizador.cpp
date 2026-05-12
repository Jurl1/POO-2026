#include "analizador.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>

Analizador::Analizador(QObject *parent)
    : QObject(parent)
    , m_manager(new QNetworkAccessManager(this))
{
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &Analizador::onRespuestaRecibida);
}

void Analizador::analizar(const QString &transcripcion, const QString &tema, const QString &apiKey)
{
    if (apiKey.trimmed().isEmpty()) {
        emit error("Ingresá tu API Key de Gemini antes de analizar.");
        return;
    }

    emit progreso("Enviando transcripción a Gemini...");

    QString modelo = "gemini-2.5-flash";
    QUrl url(QString("https://generativelanguage.googleapis.com/v1/models/%1:generateContent?key=%2")
                 .arg(modelo, apiKey.trimmed()));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Construir el body según el formato de Gemini
    QJsonObject parte;
    parte["text"] = construirPrompt(transcripcion, tema);

    QJsonArray partes;
    partes.append(parte);

    QJsonObject contenido;
    contenido["parts"] = partes;

    QJsonArray contenidos;
    contenidos.append(contenido);

    // Configuración de generación: baja temperatura para respuestas estructuradas
    QJsonObject generationConfig;
    generationConfig["temperature"] = 0.2;
    generationConfig["maxOutputTokens"] = 4096;

    QJsonObject body;
    body["contents"] = contenidos;
    body["generationConfig"] = generationConfig;

    m_manager->post(request, QJsonDocument(body).toJson());
}

QString Analizador::construirPrompt(const QString &transcripcion, const QString &tema) const
{
    return QString(
        "Analizá la siguiente transcripción de una reunión sobre el tema: \"%1\".\n\n"
        "TRANSCRIPCIÓN:\n%2\n\n"
        "Respondé ÚNICAMENTE con un JSON válido (sin markdown, sin ```json, sin ningún texto extra) "
        "con esta estructura exacta:\n"
        "{\n"
        "  \"participantes\": [\"Nombre1\", \"Nombre2\"],\n"
        "  \"resumen_ejecutivo\": \"Párrafo breve con los puntos clave de la reunión.\",\n"
        "  \"acta\": \"Texto completo del acta formal con fecha, participantes, puntos tratados y conclusiones.\",\n"
        "  \"tareas\": [\n"
        "    {\"participante\": \"Nombre1\", \"tarea\": \"Descripción de la tarea\", \"plazo\": \"Fecha o plazo si se menciona\"},\n"
        "    {\"participante\": \"Nombre2\", \"tarea\": \"Otra tarea\", \"plazo\": \"\"}\n"
        "  ]\n"
        "}"
    ).arg(tema, transcripcion);
}

void Analizador::onRespuestaRecibida(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        // Intentar leer el cuerpo del error para dar un mensaje más útil
        QByteArray cuerpoError = reply->readAll();
        QJsonDocument docError = QJsonDocument::fromJson(cuerpoError);
        if (!docError.isNull() && docError.isObject()) {
            QString msg = docError.object()["error"].toObject()["message"].toString();
            if (!msg.isEmpty()) {
                emit error("Error de Gemini: " + msg);
                return;
            }
        }
        emit error("Error de red: " + reply->errorString());
        return;
    }

    QByteArray respuestaRaw = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(respuestaRaw);

    if (doc.isNull()) {
        emit error("Respuesta inválida de la API.");
        return;
    }

    QJsonObject root = doc.object();

    // Verificar error explícito de la API
    if (root.contains("error")) {
        QString msg = root["error"].toObject()["message"].toString();
        emit error("Error de Gemini: " + msg);
        return;
    }

    // Extraer el texto de la respuesta de Gemini
    // Estructura: candidates[0].content.parts[0].text
    QString contenido = root["candidates"]
                            .toArray().first().toObject()
                            ["content"].toObject()
                            ["parts"].toArray().first().toObject()
                            ["text"].toString().trimmed();

    if (contenido.isEmpty()) {
        emit error("Gemini no devolvió contenido. Revisá la API Key o el texto de la reunión.");
        return;
    }

    emit progreso("Respuesta recibida. Procesando...");

    // Gemini a veces envuelve el JSON en ```json ... ``` aunque se lo pidamos sin eso
    if (contenido.startsWith("```")) {
        int inicio = contenido.indexOf('\n') + 1;
        int fin = contenido.lastIndexOf("```");
        if (fin > inicio) contenido = contenido.mid(inicio, fin - inicio).trimmed();
    }

    ResultadoAnalisis resultado = parsearRespuesta(contenido);
    emit analisisCompleto(resultado);
}

ResultadoAnalisis Analizador::parsearRespuesta(const QString &json) const
{
    ResultadoAnalisis resultado;

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        resultado.resumenEjecutivo = "Error al parsear la respuesta.\n\nContenido recibido:\n" + json;
        return resultado;
    }

    QJsonObject obj = doc.object();

    resultado.resumenEjecutivo = obj["resumen_ejecutivo"].toString();
    resultado.acta             = obj["acta"].toString();

    for (const QJsonValue &v : obj["participantes"].toArray())
        resultado.participantes.append(v.toString());

    // Agrupar tareas por participante y formatear como texto
    QMap<QString, QStringList> mapa;
    for (const QJsonValue &v : obj["tareas"].toArray()) {
        QJsonObject t = v.toObject();
        QString quien = t["participante"].toString();
        QString que   = t["tarea"].toString();
        QString plazo = t["plazo"].toString();
        QString linea = "  • " + que;
        if (!plazo.isEmpty()) linea += "  [" + plazo + "]";
        mapa[quien].append(linea);
    }

    QString tareas;
    for (auto it = mapa.begin(); it != mapa.end(); ++it)
        tareas += "▶ " + it.key() + ":\n" + it.value().join("\n") + "\n\n";

    resultado.tareasPorParticipante = tareas.trimmed();
    return resultado;
}
