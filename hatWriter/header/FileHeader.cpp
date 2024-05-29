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
    std::getline(std::cin, patient.name);

    std::cout << "Ingrese el apellido del paciente: ";
    std::getline(std::cin, patient.lastName);

    std::cout << "Ingrese la edad del paciente: ";
    std::cin >> patient.age;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpia el búfer de entrada

    std::cout << "Ingrese el sexo del paciente (M o F): ";
    std::getline(std::cin, patient.gender);

    std::cout << "Ingrese la fecha de nacimiento del paciente: ";
    std::getline(std::cin, patient.dateOfBirth);

    std::cout << "Ingrese la dirección del paciente: ";
    std::getline(std::cin, patient.address);

    std::cout << "Ingrese el celular del paciente: ";
    std::getline(std::cin, patient.phone);

    std::cout << "Ingrese el email del paciente: ";
    std::getline(std::cin, patient.email);

    std::cout << "Ingrese el tipo de sangre del paciente: ";
    std::getline(std::cin, patient.bloodType);

    std::cout << "Ingrese las alergias del paciente: ";
    std::getline(std::cin, patient.allergies);

    std::cout << "Ingrese las enfermedades del paciente: ";
    std::getline(std::cin, patient.diseases);

    std::cout << "Ingrese las cirugías que ha tenido el paciente: ";
    std::getline(std::cin, patient.surgeries);

    std::cout << "Ingrese las observaciones realizadas sobre el paciente: ";
    std::getline(std::cin, patient.observations);

    return patient;
}

Image createImageFromPath(string imagePath)
{
    Mat image = imread(imagePath);

    if (image.empty())
    {
        cerr << "Error al cargar la imagen." << endl;
        exit(EXIT_FAILURE);
    }

    string name = imagePath.substr(imagePath.find_last_of("/\\") + 1);
    string type = imagePath.substr(imagePath.find_last_of(".") + 1);

    int width = image.cols;
    int height = image.rows;

    // Obtener el tamaño del archivo
    ifstream file(imagePath, ios::binary | ios::ate);
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }
    string weightStr = to_string(file.tellg());

    Image img;
    img.name = name;
    img.type = type;
    img.width = width;
    img.height = height;
    img.weight = weightStr;

    return img;
}

void writeString(ofstream &outFile, const std::string &str)
{
    size_t len = str.length();
    outFile.write(reinterpret_cast<const char *>(&len), sizeof(len));
    outFile.write(str.c_str(), len);
}

void writePatient(ofstream &outFile, const Patient &patient)
{
    writeString(outFile, patient.name);
    writeString(outFile, patient.lastName);
    outFile.write(reinterpret_cast<const char *>(&patient.age), sizeof(patient.age));
    writeString(outFile, patient.gender);
    writeString(outFile, patient.dateOfBirth);
    writeString(outFile, patient.address);
    writeString(outFile, patient.phone);
    writeString(outFile, patient.email);
    writeString(outFile, patient.bloodType);
    writeString(outFile, patient.allergies);
    writeString(outFile, patient.diseases);
    writeString(outFile, patient.surgeries);
    writeString(outFile, patient.observations);
}

void writeImage(ofstream &outFile, const Image &image)
{
    writeString(outFile, image.name);
    writeString(outFile, image.type);
    outFile.write(reinterpret_cast<const char *>(&image.width), sizeof(image.width));
    outFile.write(reinterpret_cast<const char *>(&image.height), sizeof(image.height));
    writeString(outFile, image.weight);
}

void writeHeader(ofstream &outFile, const FileHeader &header)
{
    writeString(outFile, header.fileType);
    writeString(outFile, header.version);
    writeString(outFile, header.creation_date);
    writePatient(outFile, header.patient);
    writeImage(outFile, header.image);
}
