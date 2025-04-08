
/*
    Proyecto: BloodDatabase (Adaptado)
    Curso: Fundamentos de Programaci�n Orientada a Objetos (FPOO)
    Universidad del Valle

    Descripci�n:
    Este proyecto gestiona una base de datos de donantes de sangre, proporcionando
    funcionalidades para registrar, buscar y analizar la informaci�n de los donantes.

    El c�digo se bas� en el proyecto BloodDatabase, fue traducido al espa�ol
    y adaptado a las necesidades del curso.



    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    Fecha: Octubre 2024
*/
#include "BloodDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <algorithm>

using namespace std;

void BloodDatabase::displayProvinces() {
    std::cout << "Elige el departamento:\n";
    std::cout << "1. Putumayo\n";
    std::cout << "2. Cauca\n";
    std::cout << "3. Valle del Cauca\n";
    std::cout << "4. Amazonas\n";
    std::cout << "5. Risaralda\n";
    std::cout << "6. Antioquia\n";
    std::cout << "7. Norte de Santander\n";
}

void BloodDatabase::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    //   system("clear");
#endif
}

void BloodDatabase::waitForKeyPress() {
    std::cout << "Presiona cualquier tecla para continuar...";
    std::cin.ignore();
    std::cin.get();
}

int BloodDatabase::getValidatedInput(const std::string& prompt) {
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

void BloodDatabase::getDonorDetails() {
    clearConsole();
    std::cout << "Ingrese los detalles del donante\n";

    Donor newDonor;
    newDonor.donorId = getValidatedInput("Id: ");
    std::cout << "Nombre: ";
    std::getline(std::cin, newDonor.name);
    std::cout << "Direcci�n: ";
    std::getline(std::cin, newDonor.address);

    displayProvinces();
    newDonor.district = getValidatedInput("departamento (ingrese el n�mero correspondiente): ");
    std::cout << "Tipo de sangre: ";
    std::getline(std::cin, newDonor.bloodType);
    newDonor.number = getValidatedInput("N�mero: ");

    donors.push_back(newDonor);
}

void BloodDatabase::writeDataToFile() {
    std::ofstream outfile(fileName, std::ios::app);

    if (!outfile) {
        std::cout << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    Donor newDonor = donors.back();
    outfile << newDonor.donorId << ",    " << newDonor.name << ",    " << newDonor.address << ",    " << newDonor.district << ",    " << newDonor.bloodType << ",    " << newDonor.number << std::endl;

    outfile.close();
}

void BloodDatabase::searchAndDisplay() const {
    clearConsole();
    displayProvinces();
    int provinceName = getValidatedInput("Ingrese el n�mero de la departamento: ");

    std::cout << "Ingrese la direcci�n (dejar en blanco para omitir): ";
    std::string addressFilter;
    std::getline(std::cin, addressFilter);

    std::cout << "Ingrese el tipo de sangre (dejar en blanco para omitir): ";
    std::string bloodTypeFilter;
    std::getline(std::cin, bloodTypeFilter);

    std::ifstream inFile(fileName);

    if (!inFile) {
        std::cout << "Error al abrir el archivo para leer." << std::endl;
        return;
    }

    std::vector<Donor> donors;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        bool match = d.district == provinceName &&
            (addressFilter.empty() || d.address.find(addressFilter) != std::string::npos) &&
            (bloodTypeFilter.empty() || d.bloodType == bloodTypeFilter);

        if (match) {
            donors.push_back(d);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No se encontraron personas de la departamento " << provinceName;
        if (!addressFilter.empty()) {
            std::cout << " con direcci�n que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        std::cout << "." << std::endl;
    } else {
        std::cout << "Personas de la departamento " << provinceName;
        if (!addressFilter.empty()) {
            std::cout << " con direcci�n que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        std::cout << ":" << std::endl;
        for (const auto& d : donors) {
            std::cout << "Nombre: " << d.name << std::endl;
            std::cout << "Direcci�n: " << d.address << std::endl;
            std::cout << "departamento: " << d.district << std::endl;
            std::cout << "Tipo de sangre: " << d.bloodType << std::endl;
            std::cout << "N�mero de m�vil: " << d.number << std::endl;
            std::cout << std::endl;
        }
    }

    inFile.close();
    waitForKeyPress();
}

void BloodDatabase::deleteDonor(const std::string& donorName) {
    std::ifstream inFile(fileName);
    std::ofstream tempFile("temp.txt");

    if (!inFile) {
        std::cerr << "Error al abrir el archivo " << fileName << std::endl;
        return;
    }

    if (!tempFile) {
        std::cerr << "Error al crear el archivo temporal" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        if (d.name == donorName) {
            found = true;
            std::cout << "Nombre: " << d.name << std::endl;
            std::cout << "Direcci�n: " << d.address << std::endl;
            std::cout << "Tipo de sangre: " << d.bloodType << std::endl;
            std::cout << "N�mero de m�vil: " << d.number << std::endl;
            std::cout << std::endl;
            std::cout << "�Est� seguro de que desea eliminar al donante? [s/n]: ";
            char sureChoice;
            std::cin >> sureChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descartar cualquier entrada extra

            if (sureChoice == 's' || sureChoice == 'S') {
                continue;
            }
        }

        tempFile << d.donorId << ",    " << d.name << ",    " << d.address << ",    " << d.district << ",    " << d.bloodType << ",    " << d.number << std::endl;
    }

    inFile.close();
    tempFile.close();

    if (std::remove(fileName.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo original" << std::endl;
        return;
    }

    if (std::rename("temp.txt", fileName.c_str()) != 0) {
        std::cerr << "Error al renombrar el archivo temporal" << std::endl;
        return;
    }

    if (!found) {
        std::cout << "No se encontr� ning�n donante con el nombre " << donorName << std::endl;
    }
}
