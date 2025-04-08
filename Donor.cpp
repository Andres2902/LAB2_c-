
/*
    Proyecto: BloodDatabase (Adaptado)
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Descripción:
    Este proyecto gestiona una base de datos de donantes de sangre, proporcionando
    funcionalidades para registrar, buscar y analizar la información de los donantes.

    El código se basó en el proyecto BloodDatabase, fue traducido al español
    y adaptado a las necesidades del curso.



    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    Fecha: Octubre 2024
*/
#include "Donor.h"
#include <iostream>
#include <sstream>
#include <vector>

// Constructor
Donor::Donor(int id, const std::string& n, const std::string& a, const std::string& d, const std::string& b, const std::string& p)
    : donorId(id), name(n), address(a), district(d), bloodType(b), phone(p) {}

// Getters
int Donor::getId() const { return donorId; }
std::string Donor::getName() const { return name; }
std::string Donor::getAddress() const { return address; }
std::string Donor::getDistrict() const { return district; }
std::string Donor::getBloodType() const { return bloodType; }
std::string Donor::getPhone() const { return phone; }

// Setters con validación
void Donor::setId(int id) {
    if (id <= 0) {
        throw std::invalid_argument("El ID debe ser un número positivo");
    }
    donorId = id;
}

bool Donor::setName(const std::string& n) {
    if (n.empty()) {
        std::cerr << "El nombre no puede estar vacío" << std::endl;
        return false;
    }
    name = n;
    return true;
}

bool Donor::setAddress(const std::string& a) {
    if (a.empty()) {
        std::cerr << "La dirección no puede estar vacía" << std::endl;
        return false;
    }
    address = a;
    return true;
}

bool Donor::setDistrict(const std::string& d) {
    if (d.empty()) {
        std::cerr << "El distrito no puede estar vacío" << std::endl;
        return false;
    }
    district = d;
    return true;
}

bool Donor::setBloodType(const std::string& b) {
    if (!Utils::validarTipoSangre(b)) {
        std::cerr << "Tipo de sangre invalido. Tipos validos: A+, A-, B+, B-, AB+, AB-, O+, O-" << std::endl;
        return false;
    }
    bloodType = b;
    return true;
}

bool Donor::setPhone(const std::string& p) {
    if (!PhoneValidator::validarNumero(p)) {
        std::cerr << "Numero de telefono invalido" << std::endl;
        return false;
    }
    phone = p;
    return true;
}

// Método para mostrar la información del donante
void Donor::mostrar() const {
    std::cout << "ID: " << donorId << ", Nombre: " << name << ", Dirección: " << address
         << ", Distrito: " << district << ", Sangre: " << bloodType << ", Teléfono: " << phone << std::endl;
}

// Método para serializar el donante a formato de texto
std::string Donor::serializar() const {
    std::stringstream ss;
    ss << donorId << ",    " << name << ",    " << address << ",    "
       << district << ",    " << bloodType << ",    " << phone;
    return ss.str();
}

// Método estático para deserializar una línea de texto en un objeto Donor
Donor Donor::deserializar(const std::string& linea) {
    std::stringstream ss(linea);
    std::string campo;
    std::vector<std::string> campos;

    while (std::getline(ss, campo, ',')) {
        campos.push_back(Utils::trim(campo));
    }

    if (campos.size() != 6) {
        std::cerr << "Línea inválida en data.txt: faltan campos → " << linea << std::endl;
        return Donor();
    }

    try {
        int id = std::stoi(campos[0]);
        Donor donor;
        donor.setId(id);
        donor.setName(campos[1]);
        donor.setAddress(campos[2]);
        donor.setDistrict(campos[3]);
        donor.setBloodType(campos[4]);
        donor.setPhone(campos[5]);
        return donor;
    } catch (const std::exception& e) {
        std::cerr << "Error al deserializar la línea: " << e.what() << std::endl;
        return Donor();
    }
}
