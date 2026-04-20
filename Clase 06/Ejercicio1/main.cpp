#include <iostream>
#include <vector>

class Poste {
private:
    int altura;      // en metros
    float diametro;  // en cm

public:
    Poste(int a, float d) : altura(a), diametro(d) {}

    int getAltura() const { return altura; }
    float getDiametro() const { return diametro; }
};

int main() {
    std::vector<Poste> postes = {
        Poste(10, 25.5f),
        Poste(4, 12.0f),
        Poste(7, 20.0f),
        Poste(2, 10.5f),
        Poste(6, 18.2f)
    };

    std::cout << "--- Postes antes de ordenar ---\n";
    for (const auto& p : postes) {
        std::cout << "Altura: " << p.getAltura() << " m, Diametro: " << p.getDiametro() << " cm\n";
    }

    // Ordenamiento de menor a mayor según la altura
    for (size_t i = 0; i < postes.size() - 1; ++i) {
        for (size_t j = 0; j < postes.size() - i - 1; ++j) {
            if (postes[j].getAltura() > postes[j+1].getAltura()) {
                Poste temp = postes[j];
                postes[j] = postes[j+1];
                postes[j+1] = temp;
            }
        }
    }

    std::cout << "\n--- Postes despues de ordenar ---\n";
    for (const auto& p : postes) {
        std::cout << "Altura: " << p.getAltura() << " m, Diametro: " << p.getDiametro() << " cm\n";
    }

    return 0;
}