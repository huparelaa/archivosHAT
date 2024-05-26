#include "FileHeader.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Patient getPatientData()
{
    Patient patient;

    std::cout << "Ingrese el nombre del paciente: ";
    std::cin.getline(patient.name, 50);

    std::cout << "Ingrese el apellido del paciente: ";
    std::cin.getline(patient.lastName, 50);

    std::cout << "Ingrese la edad del paciente: ";
    std::cin >> patient.age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer de entrada porque inmediatamente voy a usar .getline

    std::cout << "Ingrese el sexo del paciente: (M o F)";
    std::cin.getline(patient.gender, 2);

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

    return patient;
}

Image createImageFromPath(string imagePath) {
    Mat image = imread(imagePath);

    if (image.empty()) {
        cerr << "Error al cargar la imagen." << endl;
        exit(EXIT_FAILURE);
    }

    string name = imagePath.substr(imagePath.find_last_of("/\\") + 1);
    string type = imagePath.substr(imagePath.find_last_of(".") + 1);

    int width = image.cols;
    int height = image.rows;

    // Obtener el tamaño del archivo
    ifstream file(imagePath, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }
    string weightStr = to_string(file.tellg());
    
    Image img;

    // Asegurándose de no copiar fuera de los límites del array
    strncpy(img.name, name.c_str(), sizeof(img.name) - 1);
    img.name[sizeof(img.name) - 1] = '\0'; // Asegurar terminación de la cadena

    strncpy(img.type, type.c_str(), sizeof(img.type) - 1);
    img.type[sizeof(img.type) - 1] = '\0'; // Asegurar terminación de la cadena

    img.width = width;
    img.height = height;

    strncpy(img.weight, weightStr.c_str(), sizeof(img.weight) - 1);
    img.weight[sizeof(img.weight) - 1] = '\0'; // Asegurar terminación de la cadena

    return img;
}