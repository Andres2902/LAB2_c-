
/*
    Clase: Donor
    Curso: Fundamentos de Programaci�n Orientada a Objetos (FPOO)
    Universidad del Valle

    Informaci�n CRC:

    Clase: Donor

    Responsabilidades:
        - Almacenar y gestionar la informaci�n de un donante,
          incluyendo detalles como nombre, tipo de sangre,
          distrito de residencia y otros datos relevantes.
        - Proveer m�todos para obtener y manipular dicha informaci�n,
          como  obtener datos del donante.
        - Ofrecer funcionalidades para procesar y mostrar la informaci�n
          de los donantes en formato adecuado.

    Colaboradores:
        - Colabora con la clase BloodDatabase, que gestiona una colecci�n
          de objetos Donor para administrar la base de datos de donantes
          de sangre.

    Este es un proyecto del curso FPOO de la Universidad del Valle,
    desarrollado con fines acad�micos. Puede ser utilizado con fines
    acad�micos dando los cr�ditos de la autor�a.

    El c�digo se bas� en el proyecto BloodDatabase, fue traducido al espa�ol
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

    // M�todos de acceso (getters)
    int getId() const;
    std::string getName() const;
    std::string getAddress() const;
    std::string getDistrict() const;
    std::string getBloodType() const;
    std::string getPhone() const;

    // M�todos de modificaci�n (setters) con validaci�n
    void setId(int id);
    bool setName(const std::string& n);
    bool setAddress(const std::string& a);
    bool setDistrict(const std::string& d);
    bool setBloodType(const std::string& b);
    bool setPhone(const std::string& p);

    // M�todo para mostrar la informaci�n del donante
    void mostrar() const;

    // M�todo para convertir el donante a una l�nea de texto para almacenamiento
    std::string serializar() const;

    // M�todo est�tico para crear un donante a partir de una l�nea de texto
    static Donor deserializar(const std::string& linea);

    // Alias para mantener compatibilidad con c�digo existente
    static Donor parseLine(const std::string& line) {
        return deserializar(line);
    }
};

#endif
