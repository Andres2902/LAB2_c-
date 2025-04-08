
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
#include <sstream>
#include <iostream>
#include <algorithm>

void Donor::donorDetails() const {
    std::cout << "Nombre del donante: " << name << std::endl;
    std::cout << "Distrito del donante: " << district << std::endl;
    std::cout << "Tipo de sangre del donante: " << bloodType << std::endl;
}

Donor Donor::parseLine(const std::string& line) {
    Donor d;
    std::stringstream ss(line);
    std::string token;

    getline(ss, token, ','); d.donorId = std::stoi(trim(token));
    getline(ss, token, ','); d.name = trim(token);
    getline(ss, token, ','); d.address = trim(token);
    getline(ss, token, ','); d.district = std::stoi(trim(token));
    getline(ss, token, ','); d.bloodType = trim(token);
    getline(ss, token, ','); d.number = std::stoi(trim(token));

    return d;
}

std::string Donor::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
