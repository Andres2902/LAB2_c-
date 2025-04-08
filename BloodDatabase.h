
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
#include <map>
#include "Donor.h"
#include "Utils.h"

// Interfaz p�blica para BloodDatabase
class IBloodDatabase {
public:
    virtual void getDonorDetails() = 0;
    virtual void writeDataToFile() = 0;
    virtual void searchAndDisplay() const = 0;
    virtual void deleteDonor(const std::string& donorName) = 0;
    virtual void showStatistics() const = 0;
    virtual ~IBloodDatabase() {}
};

class BloodDatabase : public IBloodDatabase {
private:
    const std::string fileName = "data.txt";
    std::vector<Donor> donors;

    // M�todos privados de utilidad
    static void displayProvinces();
    void loadDonorsFromFile() const;
    std::vector<std::string> getAllBloodTypes() const;

public:
    // Constructor
    BloodDatabase();

    // Implementaci�n de la interfaz
    void getDonorDetails() override;
    void writeDataToFile() override;
    void searchAndDisplay() const override;
    void deleteDonor(const std::string& donorName) override;
    void showStatistics() const override;

    // M�todos adicionales para an�lisis de datos
    std::map<std::string, int> getBloodTypeFrequency() const;
    std::map<std::string, double> getBloodTypePercentages() const;
    std::string getMostCommonBloodType() const;
};

#endif
