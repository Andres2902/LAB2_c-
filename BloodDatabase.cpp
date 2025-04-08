
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
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>

// Constructor
BloodDatabase::BloodDatabase() {
    // Intentar cargar los donantes existentes al inicializar
    loadDonorsFromFile();
}

// M�todo para mostrar las provincias disponibles
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

// M�todo para cargar donantes desde el archivo
void BloodDatabase::loadDonorsFromFile() const {
    std::ifstream inFile(fileName);
    if (!inFile) {
        return; // Si el archivo no existe, simplemente retornamos
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            Donor donor = Donor::deserializar(line);
            if (donor.getId() > 0) { // Solo agregar donantes v�lidos
                const_cast<BloodDatabase*>(this)->donors.push_back(donor);
            }
        }
    }
    inFile.close();
}

// M�todo para obtener todos los tipos de sangre de los donantes
std::vector<std::string> BloodDatabase::getAllBloodTypes() const {
    std::vector<std::string> bloodTypes;

    // Si no hay donantes cargados, cargarlos desde el archivo
    if (donors.empty()) {
        loadDonorsFromFile();
    }

    for (const auto& donor : donors) {
        bloodTypes.push_back(donor.getBloodType());
    }

    return bloodTypes;
}

// M�todo para obtener la frecuencia de cada tipo de sangre
std::map<std::string, int> BloodDatabase::getBloodTypeFrequency() const {
    std::vector<std::string> bloodTypes = getAllBloodTypes();
    return Utils::contarFrecuencia(bloodTypes);
}

// M�todo para calcular el porcentaje de cada tipo de sangre
std::map<std::string, double> BloodDatabase::getBloodTypePercentages() const {
    std::map<std::string, int> frequency = getBloodTypeFrequency();
    int totalDonors = getAllBloodTypes().size();

    if (totalDonors == 0) {
        return std::map<std::string, double>();
    }

    return Utils::calcularPorcentajes(frequency, totalDonors);
}

// M�todo para obtener el tipo de sangre m�s com�n
std::string BloodDatabase::getMostCommonBloodType() const {
    std::map<std::string, int> frequency = getBloodTypeFrequency();
    return Utils::encontrarMasFrecuente(frequency);
}

// M�todo para mostrar estad�sticas sobre tipos de sangre
void BloodDatabase::showStatistics() const {
    Utils::clearConsole();
    std::cout << "=== ESTAD�STICAS DE TIPOS DE SANGRE ===" << std::endl;

    std::map<std::string, double> percentages = getBloodTypePercentages();
    std::string mostCommon = getMostCommonBloodType();

    if (percentages.empty()) {
        std::cout << "No hay datos suficientes para generar estad�sticas." << std::endl;
        Utils::waitForKeyPress();
        return;
    }

    std::cout << "Porcentaje de cada tipo de sangre:" << std::endl;
    for (const auto& pair : percentages) {
        std::cout << "  " << pair.first << ": " << std::fixed << std::setprecision(2) << pair.second << "%" << std::endl;
    }

    std::cout << "\nTipo de sangre predominante: " << mostCommon << std::endl;

    Utils::waitForKeyPress();
}

// M�todo para obtener detalles del donante del usuario
void BloodDatabase::getDonorDetails() {
    Utils::clearConsole();
    std::cout << "Ingrese los detalles del donante\n";

    Donor newDonor;

    // Solicitar y validar ID
    int id = Utils::getValidatedInput("ID: ");
    try {
        newDonor.setId(id);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        Utils::waitForKeyPress();
        return;
    }

    // Solicitar y validar nombre
    std::string name;
    std::cout << "Nombre: ";
    std::getline(std::cin, name);
    if (!newDonor.setName(name)) {
        Utils::waitForKeyPress();
        return;
    }

    // Solicitar y validar direcci�n
    std::string address;
    std::cout << "Direcci�n: ";
    std::getline(std::cin, address);
    if (!newDonor.setAddress(address)) {
        Utils::waitForKeyPress();
        return;
    }

    // Solicitar y validar distrito
    displayProvinces();
    int districtNum = Utils::getValidatedInput("Departamento (ingrese el n�mero correspondiente): ");
    if (districtNum < 1 || districtNum > 7) {
        std::cerr << "N�mero de departamento inv�lido" << std::endl;
        Utils::waitForKeyPress();
        return;
    }
    if (!newDonor.setDistrict(std::to_string(districtNum))) {
        Utils::waitForKeyPress();
        return;
    }

    // Solicitar y validar tipo de sangre
    std::string bloodType;
    std::cout << "Tipo de sangre (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
    std::getline(std::cin, bloodType);
    if (!newDonor.setBloodType(bloodType)) {
        Utils::waitForKeyPress();
        return;
    }

    // Solicitar y validar n�mero de tel�fono
    std::string phone;
    std::cout << "N�mero de tel�fono: ";
    std::getline(std::cin, phone);
    if (!newDonor.setPhone(phone)) {
        Utils::waitForKeyPress();
        return;
    }

    donors.push_back(newDonor);
    std::cout << "Donante registrado con �xito." << std::endl;
    Utils::waitForKeyPress();
}

// M�todo para escribir datos en el archivo
void BloodDatabase::writeDataToFile() {
    std::ofstream outfile(fileName, std::ios::app);

    if (!outfile) {
        std::cerr << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    Donor newDonor = donors.back();
    outfile << newDonor.serializar() << std::endl;

    outfile.close();
}

// M�todo para buscar y mostrar donantes seg�n criterios
void BloodDatabase::searchAndDisplay() const {
    Utils::clearConsole();
    displayProvinces();
    int provinceName = Utils::getValidatedInput("Ingrese el n�mero del departamento: ");

    std::cout << "Ingrese la direcci�n (dejar en blanco para omitir): ";
    std::string addressFilter;
    std::getline(std::cin, addressFilter);

    std::cout << "Ingrese el tipo de sangre (dejar en blanco para omitir): ";
    std::string bloodTypeFilter;
    std::getline(std::cin, bloodTypeFilter);

    // Cargar donantes si es necesario
    if (donors.empty()) {
        loadDonorsFromFile();
    }

    std::vector<Donor> foundDonors;
    bool found = false;

    for (const auto& donor : donors) {
        bool match = donor.getDistrict() == std::to_string(provinceName) &&
            (addressFilter.empty() || donor.getAddress().find(addressFilter) != std::string::npos) &&
            (bloodTypeFilter.empty() || donor.getBloodType() == bloodTypeFilter);

        if (match) {
            foundDonors.push_back(donor);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No se encontraron personas del departamento " << provinceName;
        if (!addressFilter.empty()) {
            std::cout << " con direcci�n que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        std::cout << "." << std::endl;
    } else {
        std::cout << "Personas del departamento " << provinceName;
        if (!addressFilter.empty()) {
            std::cout << " con direcci�n que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            std::cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        std::cout << ":" << std::endl;
        for (const auto& d : foundDonors) {
            std::cout << "Nombre: " << d.getName() << std::endl;
            std::cout << "Direcci�n: " << d.getAddress() << std::endl;
            std::cout << "Departamento: " << d.getDistrict() << std::endl;
            std::cout << "Tipo de sangre: " << d.getBloodType() << std::endl;
            std::cout << "N�mero de m�vil: " << d.getPhone() << std::endl;
            std::cout << std::endl;
        }
    }

    Utils::waitForKeyPress();
}

// M�todo para eliminar un donante por nombre
void BloodDatabase::deleteDonor(const std::string& donorName) {
    // Cargar donantes si es necesario
    if (donors.empty()) {
        loadDonorsFromFile();
    }

    bool found = false;
    size_t index = 0;

    // Buscar el donante por nombre
    for (size_t i = 0; i < donors.size(); i++) {
        if (donors[i].getName() == donorName) {
            found = true;
            index = i;
            break;
        }
    }

    if (!found) {
        std::cout << "No se encontr� ning�n donante con el nombre " << donorName << std::endl;
        Utils::waitForKeyPress();
        return;
    }

    // Mostrar informaci�n del donante
    const Donor& donor = donors[index];
    std::cout << "Nombre: " << donor.getName() << std::endl;
    std::cout << "Direcci�n: " << donor.getAddress() << std::endl;
    std::cout << "Tipo de sangre: " << donor.getBloodType() << std::endl;
    std::cout << "N�mero de m�vil: " << donor.getPhone() << std::endl;
    std::cout << std::endl;

    // Confirmar eliminaci�n
    std::cout << "�Est� seguro de que desea eliminar al donante? [s/n]: ";
    char sureChoice;
    std::cin >> sureChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (sureChoice == 's' || sureChoice == 'S') {
        // Eliminar el donante de la lista
        donors.erase(donors.begin() + index);

        // Reescribir todo el archivo
        std::ofstream outfile(fileName);
        if (!outfile) {
            std::cerr << "Error al abrir el archivo para escribir." << std::endl;
            Utils::waitForKeyPress();
            return;
        }

        for (const auto& d : donors) {
            outfile << d.serializar() << std::endl;
        }

        outfile.close();
        std::cout << "Donante eliminado con �xito." << std::endl;
    } else {
        std::cout << "Operaci�n cancelada." << std::endl;
    }

    Utils::waitForKeyPress();
}
