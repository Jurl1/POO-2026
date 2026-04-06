#include <iostream>
#include <vector>

class Pixel9ProXL {
private:
    int almacenamientoGB;
    float bateriaPorcentaje;
    bool esRefurbishedPremium;
    
    // Parámetros de temperatura
    float tempBateriaCelsius;
    float tempBateriaFahrenheit;

    // Parámetros de telemetría / desplazamiento
    float velocidadActualKmh;
    float velocidadActualMph;

public:
    // Constructores
    Pixel9ProXL() 
        : almacenamientoGB(256), bateriaPorcentaje(100.0f), esRefurbishedPremium(true) {
        setTemperaturaBateria(30.0f);
        setVelocidad(0.0f);
    }

    Pixel9ProXL(int alm, float bat, bool ref) 
        : almacenamientoGB(alm), bateriaPorcentaje(bat), esRefurbishedPremium(ref) {
        setTemperaturaBateria(30.0f);
        setVelocidad(0.0f);
    }

    // Métodos
    void setTemperaturaBateria(float celsius) {
        tempBateriaCelsius = celsius;
        tempBateriaFahrenheit = (celsius * 9.0f / 5.0f) + 32.0f;
    }

    void setVelocidad(float kmh) {
        velocidadActualKmh = kmh;
        velocidadActualMph = kmh * 0.621371f;
    }
};

int main() {
    std::vector<Pixel9ProXL> inventario;
    
    // 200 MB representados en bytes (200 * 1024 * 1024)
    long long limiteBytes = 209715200; 
    size_t sizeObjeto = sizeof(Pixel9ProXL);
    
    // Total de objetos necesarios para llegar a 200 MB
    size_t maxObjetos = limiteBytes / sizeObjeto;

    // Se reserva el espacio con anticipación para evitar la reubicación en memoria del vector
    inventario.reserve(maxObjetos);

    for (size_t i = 0; i < maxObjetos; ++i) {
        inventario.push_back(Pixel9ProXL(256, 100.0f, true));
    }

    std::cout << "Límite alcanzado.\n";
    std::cout << "Se han instanciado y agregado " << inventario.size() << " objetos.\n";
    std::cout << "Peso individual de memoria por objeto: " << sizeObjeto << " bytes.\n";
    
    return 0;
}