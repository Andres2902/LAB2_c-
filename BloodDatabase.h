
/*
    Clase: BloodDatabase
    Curso: Fundamentos de Programaci�n Orientada a Objetos (FPOO)
    Universidad del Valle

    Informaci�n CRC:

    Clase: BloodDatabase

    Responsabilidades:
        - Gestionar una base de datos de donantes de sangre, almacenando
          un conjuto de objetos de tipo `Donor`.
        - Proveer m�todos para agregar, eliminar y buscar donantes en la base de datos.
        - Facilitar el manejo de la informaci�n almacenada de forma eficiente y
          adecuada para su consulta y modificaci�n.

    Colaboradores:
        - Colabora directamente con la clase `Donor`, ya que administra una colecci�n
          de objetos `Donor`.

    Este es un proyecto del curso FPOO de la Universidad del Valle,
    desarrollado con fines acad�micos. Puede ser utilizado con fines
    acad�micos dando los cr�ditos de la autor�a.

    El c�digo se bas� en el proyecto BloodDatabase, fue traducido al espa�ol
    y adaptado a las necesidades del curso.

    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    Fecha: Octubre 2024
*/
#ifndef BLOODDATABASE_H
#define BLOODDATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Donor.h"

class BloodDatabase {
private:
    const std::string fileName = "data.txt";
    std::vector<Donor> donors;

    static void displayProvinces();

public:
    static void clearConsole();
    static void waitForKeyPress();
    static int getValidatedInput(const std::string& prompt);

    void getDonorDetails();
    void writeDataToFile();
    void searchAndDisplay() const;
    void deleteDonor(const std::string& donorName);
};

#endif // BLOODDATABASE_H
