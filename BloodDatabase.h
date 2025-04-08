
/*
    Clase: BloodDatabase
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Información CRC:

    Clase: BloodDatabase

    Responsabilidades:
        - Gestionar una base de datos de donantes de sangre, almacenando
          un conjuto de objetos de tipo `Donor`.
        - Proveer métodos para agregar, eliminar y buscar donantes en la base de datos.
        - Facilitar el manejo de la información almacenada de forma eficiente y
          adecuada para su consulta y modificación.

    Colaboradores:
        - Colabora directamente con la clase `Donor`, ya que administra una colección
          de objetos `Donor`.

    Este es un proyecto del curso FPOO de la Universidad del Valle,
    desarrollado con fines académicos. Puede ser utilizado con fines
    académicos dando los créditos de la autoría.

    El código se basó en el proyecto BloodDatabase, fue traducido al español
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

// Interfaz pública para BloodDatabase
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

    // Métodos privados de utilidad
    static void displayProvinces();
    void loadDonorsFromFile() const;
    std::vector<std::string> getAllBloodTypes() const;

public:
    // Constructor
    BloodDatabase();

    // Implementación de la interfaz
    void getDonorDetails() override;
    void writeDataToFile() override;
    void searchAndDisplay() const override;
    void deleteDonor(const std::string& donorName) override;
    void showStatistics() const override;

    // Métodos adicionales para análisis de datos
    std::map<std::string, int> getBloodTypeFrequency() const;
    std::map<std::string, double> getBloodTypePercentages() const;
    std::string getMostCommonBloodType() const;
};

#endif
