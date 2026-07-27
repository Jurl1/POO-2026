#ifndef DATAMANAGER_H
#define DATAMANAGER_H

// =============================================================================
// DataManager — Gestor de datos del sistema
//
// Responsabilidades:
//   - Almacenar el historial de análisis realizados en la sesión
//   - Proveer estadísticas (cantidad de análisis, participantes vistos)
//   - Guardar localmente en SQLite
//   - Enviar al servidor FastAPI (poo.juriserver.website) autenticándose con JWT
//   - Implementa el patrón Singleton con miembro static
// =============================================================================

#include "algoritmoIA.h"
#include <QList>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSqlDatabase>

class DataManager
{
public:
    // Singleton: devuelve la única instancia del DataManager
    static DataManager& instancia();

    // Establecer el token JWT obtenido tras el login
    void setToken(const QString &token);

    // Registra un nuevo análisis en el historial local
    void registrarAnalisis(const ResultadoAnalisis &resultado);

    // Devuelve cuántos análisis se han realizado en esta sesión
    int cantidadAnalisis() const;

    // Devuelve el historial completo de análisis
    const QList<ResultadoAnalisis>& historial() const;

    // Devuelve todos los participantes vistos en la sesión (sin duplicados)
    QStringList todosLosParticipantes() const;

    // Limpia el historial de la sesión
    void limpiarHistorial();

    // Envía el resultado del análisis al servidor MySQL vía API REST con JWT
    void enviarAlServidor(const QString &tema, const ResultadoAnalisis &resultado);

private:
    DataManager();

    DataManager(const DataManager&)            = delete;
    DataManager& operator=(const DataManager&) = delete;

    QList<ResultadoAnalisis> m_historial;

    static int m_contadorAnalisis;
    static const QString SERVER_API_URL;

    QString m_token;
    QNetworkAccessManager *m_networkManager;
    QSqlDatabase m_db;
    void inicializarBaseDeDatos();
};

#endif // DATAMANAGER_H
