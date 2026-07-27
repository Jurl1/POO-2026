#include "analizadorgemini.h"
#include "datamanager.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QMap>

// Constantes estaticas de la clase
// static: pertenecen a la clase, no a cada objeto
const QString AnalizadorGemini::MODELO        = "gemini-2.5-flash";
const QString AnalizadorGemini::ENDPOINT_BASE =
    "https://generativelanguage.googleapis.com/v1/models/%1:generateContent?key=%2";

AnalizadorGemini::AnalizadorGemini(QObject *parent)
    : AlgoritmoIA(parent)
    , m_manager(new QNetworkAccessManager(this))
{
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &AnalizadorGemini::onRespuestaRecibida);
}

QString AnalizadorGemini::nombreProveedor() const
{
    return "Google Gemini 2.5 Flash";
}

void AnalizadorGemini::analizar(const QString &transcripcion,
                                 const QString &tema,
                                 const QString &apiKey)
{
    if (apiKey.trimmed().isEmpty()) {
        emit error("Ingresa tu API Key de Gemini antes de analizar.");
        return;
    }
    if (transcripcion.trimmed().isEmpty()) {
        emit error("La transcripcion esta vacia.");
        return;
    }

    emit progreso("Enviando transcripcion a " + nombreProveedor() + "...");

    QUrl url(ENDPOINT_BASE.arg(MODELO, apiKey.trimmed()));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Construir body segun el formato de Gemini
    QJsonObject parte;
    parte["text"] = construirPrompt(transcripcion, tema);

    QJsonArray partes;
    partes.append(parte);

    QJsonObject contenido;
    contenido["parts"] = partes;

    QJsonArray contenidos;
    contenidos.append(contenido);

    QJsonObject generationConfig;
    generationConfig["temperature"]    = 0.2;
    generationConfig["maxOutputTokens"] = 16384;  // amplio para transcripciones largas

    QJsonObject body;
    body["contents"]        = contenidos;
    body["generationConfig"] = generationConfig;

    m_manager->post(request, QJsonDocument(body).toJson());
}

QString AnalizadorGemini::construirPrompt(const QString &transcripcion,
                                           const QString &tema) const
{
    return QString(
        "Analiza la siguiente transcripcion de una reunion sobre el tema: \"%1\".\n\n"
        "TRANSCRIPCION:\n%2\n\n"
        "Responde UNICAMENTE con un JSON valido (sin markdown, sin ```json, sin texto extra) "
        "con esta estructura exacta:\n"
        "{\n"
        "  \"participantes\": [\"Nombre1\", \"Nombre2\"],\n"
        "  \"resumen_ejecutivo\": \"Parrafo breve con los puntos clave.\",\n"
        "  \"acta\": \"Texto completo del acta formal.\",\n"
        "  \"tareas\": [\n"
        "    {\"participante\": \"Nombre1\", \"tarea\": \"Descripcion\", \"plazo\": \"Fecha o vacio\"},\n"
        "    {\"participante\": \"Nombre2\", \"tarea\": \"Descripcion\", \"plazo\": \"\"}\n"
        "  ]\n"
        "}"
    ).arg(tema, transcripcion);
}

void AnalizadorGemini::onRespuestaRecibida(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        QByteArray cuerpo = reply->readAll();
        QJsonDocument docErr = QJsonDocument::fromJson(cuerpo);
        if (!docErr.isNull() && docErr.isObject()) {
            QString msg = docErr.object()["error"].toObject()["message"].toString();
            if (!msg.isEmpty()) { emit error("Error de Gemini: " + msg); return; }
        }
        emit error("Error de red: " + reply->errorString());
        return;
    }

    QByteArray respuestaRaw = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(respuestaRaw);

    if (doc.isNull()) {
        emit error("Respuesta invalida de la API.");
        return;
    }

    QJsonObject root = doc.object();
    if (root.contains("error")) {
        emit error("Error de Gemini: " + root["error"].toObject()["message"].toString());
        return;
    }

    // Extraer texto de la respuesta de Gemini
    QString contenido = root["candidates"]
                            .toArray().first().toObject()
                            ["content"].toObject()
                            ["parts"].toArray().first().toObject()
                            ["text"].toString().trimmed();

    if (contenido.isEmpty()) {
        emit error("Gemini no devolvio contenido. Revisa la API Key o el texto.");
        return;
    }

    emit progreso("Respuesta recibida. Procesando...");

    // Limpiar posible markdown que Gemini agrega a veces
    if (contenido.startsWith("```")) {
        int inicio = contenido.indexOf('\n') + 1;
        int fin    = contenido.lastIndexOf("```");
        if (fin > inicio) contenido = contenido.mid(inicio, fin - inicio).trimmed();
    }

    ResultadoAnalisis resultado = parsearRespuesta(contenido);

    // Registrar en DataManager antes de emitir
    DataManager::instancia().registrarAnalisis(resultado);

    emit analisisCompleto(resultado);
}

ResultadoAnalisis AnalizadorGemini::parsearRespuesta(const QString &respuestaCruda) const
{
    ResultadoAnalisis resultado;

    QJsonDocument doc = QJsonDocument::fromJson(respuestaCruda.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        resultado.resumenEjecutivo = "Error al parsear la respuesta.\n\nContenido recibido:\n"
                                     + respuestaCruda;
        resultado.valido = false;
        return resultado;
    }

    QJsonObject obj = doc.object();

    resultado.resumenEjecutivo = obj["resumen_ejecutivo"].toString();
    resultado.acta             = obj["acta"].toString();
    resultado.valido           = true;

    for (const QJsonValue &v : obj["participantes"].toArray())
        resultado.participantes.append(v.toString());

    // Agrupar tareas por participante
    QMap<QString, QStringList> mapa;
    for (const QJsonValue &v : obj["tareas"].toArray()) {
        QJsonObject t = v.toObject();
        QString quien = t["participante"].toString();
        QString que   = t["tarea"].toString();
        QString plazo = t["plazo"].toString();
        QString linea = "  * " + que;
        if (!plazo.isEmpty()) linea += "  [" + plazo + "]";
        mapa[quien].append(linea);
    }

    QString tareas;
    for (auto it = mapa.begin(); it != mapa.end(); ++it)
        tareas += "> " + it.key() + ":\n" + it.value().join("\n") + "\n\n";

    resultado.tareasPorParticipante = tareas.trimmed();
    return resultado;
}
