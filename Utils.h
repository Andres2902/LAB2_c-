#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

class Utils {
public:
    // Elimina espacios en blanco al inicio y final de la cadena
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
    }

    // Verifica si el tipo de sangre es v�lido
    static bool validarTipoSangre(const std::string& tipo) {
        static const std::vector<std::string> tiposValidos = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
        return std::find(tiposValidos.begin(), tiposValidos.end(), tipo) != tiposValidos.end();
    }

    // M�todo para limpiar la consola (multiplataforma)
    static void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }

    // M�todo para esperar la pulsaci�n de una tecla
    static void waitForKeyPress() {
        std::cout << "Presiona cualquier tecla para continuar...";
        std::cin.ignore();
        std::cin.get();
    }

    // M�todo para obtener entrada validada como n�mero
    static int getValidatedInput(const std::string& prompt) {
        int value;
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            try {
                if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
                    throw std::invalid_argument("La entrada contiene caracteres no num�ricos");
                }
                value = std::stoi(input);
                break; // si la conversi�n es exitosa, salir del bucle
            } catch (const std::invalid_argument& e) {
                std::cout << "Entrada no v�lida: " << e.what() << ". Por favor ingrese un n�mero v�lido." << std::endl;
            } catch (const std::out_of_range&) {
                std::cout << "Entrada fuera de rango. Por favor ingrese un n�mero v�lido." << std::endl;
            }
        }
        return value;
    }

    // M�todo para contar la frecuencia de valores en un vector
    static std::map<std::string, int> contarFrecuencia(const std::vector<std::string>& datos) {
        std::map<std::string, int> frecuencia;
        for (const auto& dato : datos) {
            frecuencia[dato]++;
        }
        return frecuencia;
    }

    // M�todo para calcular porcentajes
    static std::map<std::string, double> calcularPorcentajes(const std::map<std::string, int>& frecuencia, int total) {
        std::map<std::string, double> porcentajes;
        for (const auto& par : frecuencia) {
            porcentajes[par.first] = (static_cast<double>(par.second) / total) * 100.0;
        }
        return porcentajes;
    }

    // M�todo para encontrar el valor con mayor frecuencia
    static std::string encontrarMasFrecuente(const std::map<std::string, int>& frecuencia) {
        std::string masFrecuente = "";
        int maxFrec = 0;

        for (const auto& par : frecuencia) {
            if (par.second > maxFrec) {
                maxFrec = par.second;
                masFrecuente = par.first;
            }
        }

        return masFrecuente;
    }
};

#endif
