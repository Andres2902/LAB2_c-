
/*
    Clase: Donor
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Información CRC:

    Clase: Donor

    Responsabilidades:
        - Almacenar y gestionar la información de un donante,
          incluyendo detalles como nombre, tipo de sangre,
          distrito de residencia y otros datos relevantes.
        - Proveer métodos para obtener y manipular dicha información,
          como  obtener datos del donante.
        - Ofrecer funcionalidades para procesar y mostrar la información
          de los donantes en formato adecuado.

    Colaboradores:
        - Colabora con la clase BloodDatabase, que gestiona una colección
          de objetos Donor para administrar la base de datos de donantes
          de sangre.

    Este es un proyecto del curso FPOO de la Universidad del Valle,
    desarrollado con fines académicos. Puede ser utilizado con fines
    académicos dando los créditos de la autoría.

    El código se basó en el proyecto BloodDatabase, fue traducido al español
    y adaptado a las necesidades del curso.

    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    Fecha: Octubre 2024
*/
#ifndef DONOR_H
#define DONOR_H

#include <string>
#include "PhoneValidator.h"
#include "Utils.h"

class Donor {
private:
    int donorId;
    std::string name;
    std::string address;
    std::string district;
    std::string bloodType;
    std::string phone;

public:
    // Constructores
    Donor() = default;
    Donor(int id, const std::string& n, const std::string& a, const std::string& d, const std::string& b, const std::string& p);

    // Métodos de acceso (getters)
    int getId() const;
    std::string getName() const;
    std::string getAddress() const;
    std::string getDistrict() const;
    std::string getBloodType() const;
    std::string getPhone() const;

    // Métodos de modificación (setters) con validación
    void setId(int id);
    bool setName(const std::string& n);
    bool setAddress(const std::string& a);
    bool setDistrict(const std::string& d);
    bool setBloodType(const std::string& b);
    bool setPhone(const std::string& p);

    // Método para mostrar la información del donante
    void mostrar() const;

    // Método para convertir el donante a una línea de texto para almacenamiento
    std::string serializar() const;

    // Método estático para crear un donante a partir de una línea de texto
    static Donor deserializar(const std::string& linea);

    // Alias para mantener compatibilidad con código existente
    static Donor parseLine(const std::string& line) {
        return deserializar(line);
    }
};

#endif
