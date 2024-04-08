#include "FileHeader.h"
#include <iostream>
#include <fstream>
#include <limits>

void savePatientData(const Patient& patient, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&patient), sizeof(Patient));
    file.close();
}

int main() {
    Patient patient;

    std::cout << "Ingrese el nombre del paciente: ";
    std::cin.getline(patient.name, 50);
    
    std::cout << "Ingrese el apellido del paciente: ";
    std::cin.getline(patient.lastName, 50);
    
    std::cout << "Ingrese la edad del paciente: ";
    std::cin >> patient.age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer de entrada porque inmediatamente voy a usar .getline

    std::cout << "Ingrese el sexo del paciente: ";
    std::cin.getline(patient.gender, 20);

    std::cout << "Ingrese la fecha de nacimiento del paciente: ";
    std::cin.getline(patient.dateOfBirth, 20);

    std::cout << "Ingrese la dirección del paciente: ";
    std::cin.getline(patient.address, 100);

    std::cout << "Ingrese el celular del paciente: ";
    std::cin.getline(patient.phone, 20);

    std::cout << "Ingrese el email del paciente: ";
    std::cin.getline(patient.email, 50);

    std::cout << "Ingrese el tipo de sangre del paciente: ";
    std::cin.getline(patient.bloodType, 5);

    std::cout << "Ingrese las alergias del paciente: ";
    std::cin.getline(patient.allergies, 100);

    std::cout << "Ingrese las enfermedades del paciente: ";
    std::cin.getline(patient.diseases, 100);

    std::cout << "Ingrese las cirugías que ha tenído el paciente: ";
    std::cin.getline(patient.surgeries, 100);

    std::cout << "Ingrese las observaciones realizadas sobre el paciente: ";
    std::cin.getline(patient.observations, 255);

    savePatientData(patient, "patient_data.bin");

    std::cout << "Los datos del paciente se han guardado correctamente." << std::endl;

    return 0;
}