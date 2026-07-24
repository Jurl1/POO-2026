#include "datamanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

// Definición del miembro static fuera de la clase
int DataManager::m_contadorAnalisis = 0;

// URL de la API REST en el servidor HTTPS remoto (Cloudflare Tunnel)
const QString DataManager::SERVER_API_URL = "https://poo.juriserver.website/api.php";

DataManager::DataManager() : m_networkManager(nullptr)
{
    inicializarBaseDeDatos();
}

void DataManager::setToken(const QString &token)
{
    m_token = token;
}

void DataManager::inicializarBaseDeDatos()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    
    // Guardar el archivo físicamente en la carpeta principal del proyecto
    QString rutaDB = QString(PRO_DIR) + "/historial.sqlite";
    m_db.setDatabaseName(rutaDB);

    if (!m_db.open()) {
        qDebug() << "Error al abrir SQLite local:" << m_db.lastError().text();
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS analisis ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "resumen TEXT, "
               "acta TEXT, "
               "tareas TEXT, "
               "participantes TEXT)");

    // Cargar historial previo si existe
    QSqlQuery qSelect("SELECT resumen, acta, tareas, participantes FROM analisis");
    while (qSelect.next()) {
        ResultadoAnalisis r;
        r.resumenEjecutivo = qSelect.value(0).toString();
        r.acta = qSelect.value(1).toString();
        r.tareasPorParticipante = qSelect.value(2).toString();
        r.participantes = qSelect.value(3).toString().split(",", Qt::SkipEmptyParts);
        r.valido = true;
        m_historial.append(r);
        m_contadorAnalisis++;
    }
}

DataManager& DataManager::instancia()
{
    static DataManager dm;
    return dm;
}

void DataManager::registrarAnalisis(const ResultadoAnalisis &resultado)
{
    if (!resultado.valido) return;

    // Guardar localmente en SQLite
    QSqlQuery query;
    query.prepare("INSERT INTO analisis (resumen, acta, tareas, participantes) VALUES (?, ?, ?, ?)");
    query.addBindValue(resultado.resumenEjecutivo);
    query.addBindValue(resultado.acta);
    query.addBindValue(resultado.tareasPorParticipante);
    query.addBindValue(resultado.participantes.join(","));
    if (!query.exec()) {
        qDebug() << "Error al guardar en SQLite:" << query.lastError().text();
    }

    m_historial.append(resultado);
    m_contadorAnalisis++;
}

int DataManager::cantidadAnalisis() const
{
    return m_contadorAnalisis;
}

const QList<ResultadoAnalisis>& DataManager::historial() const
{
    return m_historial;
}

QStringList DataManager::todosLosParticipantes() const
{
    QStringList todos;
    for (const ResultadoAnalisis &r : m_historial) {
        for (const QString &p : r.participantes) {
            if (!todos.contains(p))
                todos.append(p);
        }
    }
    return todos;
}

void DataManager::limpiarHistorial()
{
    QSqlQuery query;
    query.exec("DELETE FROM analisis");
    m_historial.clear();
}

// Envía los datos del análisis al servidor remoto vía HTTP POST con JWT
void DataManager::enviarAlServidor(const QString &tema, const ResultadoAnalisis &resultado)
{
    if (!resultado.valido) return;

    if (!m_networkManager) {
        m_networkManager = new QNetworkAccessManager;
    }

    QJsonObject json;
    json["tema"]           = tema;
    json["resumen"]        = resultado.resumenEjecutivo;
    json["acta"]           = resultado.acta;
    json["tareas"]         = resultado.tareasPorParticipante;
    json["participantes"]  = resultado.participantes.join(", ");

    QUrl url(SERVER_API_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Incluir token JWT para autenticación en el servidor
    if (!m_token.isEmpty()) {
        request.setRawHeader("Authorization", ("Bearer " + m_token).toUtf8());
    }

    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());

    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Datos enviados al servidor MySQL remoto correctamente";
            qDebug() << "Respuesta:" << reply->readAll();
        } else {
            qDebug() << "Error al enviar datos al servidor:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
