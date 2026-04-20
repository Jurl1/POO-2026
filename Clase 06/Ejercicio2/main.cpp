#include <iostream>
#include <vector>
#include <string>

// Función de apoyo para omitir los espacios al comparar
std::string sinEspacios(const std::string& str) {
    std::string res;
    for (char c : str) {
        if (c != ' ') {
            res += c;
        }
    }
    return res;
}

int main() {
    std::vector<std::string> expresiones = {
        "pan comido",
        "a lo hecho pecho",
        "mas vale tarde que nunca",
        "al mal tiempo buena cara",
        "tirar la toalla"
    };

    for (size_t i = 0; i < expresiones.size() - 1; ++i) {
        for (size_t j = 0; j < expresiones.size() - i - 1; ++j) {
            if (sinEspacios(expresiones[j]) > sinEspacios(expresiones[j+1])) {
                std::string temp = expresiones[j];
                expresiones[j] = expresiones[j+1];
                expresiones[j+1] = temp;
            }
        }
    }

    std::cout << "Expresiones ordenadas alfabeticamente (sin espacios):\n";
    for (const auto& expr : expresiones) {
        std::cout << expr << "\n";
    }

    return 0;
}