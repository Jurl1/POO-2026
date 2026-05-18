#include "datamanager.h"

// Definicion del miembro static fuera de la clase (obligatorio en C++)
// Se inicializa en 0 una sola vez al arrancar el programa
int DataManager::m_contadorAnalisis = 0;

DataManager& DataManager::instancia()
{
    // Variable local static: se crea la primera vez que se llama instancia()
    // y persiste por toda la vida del programa. Es thread-safe en C++11+.
    static DataManager dm;
    return dm;
}

void DataManager::registrarAnalisis(const ResultadoAnalisis &resultado)
{
    if (!resultado.valido) return;

    m_historial.append(resultado);
    m_contadorAnalisis++;  // incrementa el contador estatico
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
    m_historial.clear();
    // Nota: m_contadorAnalisis NO se resetea,
    // porque cuenta el total historico de la sesion
}
