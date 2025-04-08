
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

class Donor {
public:
    int donorId, district, number;
    std::string name, address, bloodType;

    void donorDetails() const;

    static Donor parseLine(const std::string& line);

private:
    static std::string trim(const std::string& str);
};

#endif // DONOR_H
