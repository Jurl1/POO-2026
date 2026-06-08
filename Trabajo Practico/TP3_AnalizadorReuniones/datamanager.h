#ifndef DATAMANAGER_H
#define DATAMANAGER_H

// =============================================================================
// DataManager — Gestor de datos del sistema
//
// Responsabilidades:
//   - Almacenar el historial de analisis realizados en la sesion
//   - Proveer estadisticas (cantidad de analisis, participantes vistos)
//   - Implementa el patron Singleton con miembro static
//
// USO DE static:
//   - m_contadorAnalisis: cuenta analisis en toda la vida del programa,
//     independientemente de cuantos objetos DataManager existan
//   - instancia(): devuelve siempre el mismo objeto (Singleton)
//     la variable local static se inicializa solo la primera vez
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
    // Singleton: devuelve la unica instancia del DataManager
    // La variable local static garantiza que se crea una sola vez
    static DataManager& instancia();

    // Registra un nuevo analisis en el historial
    void registrarAnalisis(const ResultadoAnalisis &resultado);

    // Devuelve cuantos analisis se han realizado en esta sesion
    // (usa el contador estatico)
    int cantidadAnalisis() const;

    // Devuelve el historial completo de analisis
    const QList<ResultadoAnalisis>& historial() const;

    // Devuelve todos los participantes vistos en la sesion (sin duplicados)
    QStringList todosLosParticipantes() const;

    // Limpia el historial de la sesion
    void limpiarHistorial();

    // Envia el resultado del analisis al servidor MySQL via API REST
    void enviarAlServidor(const QString &tema, const ResultadoAnalisis &resultado);

private:
    // Constructor privado: nadie puede crear DataManager directamente
    DataManager();

    // Copia y asignacion prohibidas (patron Singleton)
    DataManager(const DataManager&)            = delete;
    DataManager& operator=(const DataManager&) = delete;

    QList<ResultadoAnalisis> m_historial;

    // static: pertenece a la clase, se comparte entre todas las instancias
    // (en este caso hay solo una, pero el concepto aplica igual)
    static int m_contadorAnalisis;

    // URL de la API REST en el servidor
    static const QString SERVER_API_URL;

    QNetworkAccessManager *m_networkManager;
    QSqlDatabase m_db;
    void inicializarBaseDeDatos();
};

#endif // DATAMANAGER_H
