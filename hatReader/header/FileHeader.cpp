#include "FileHeader.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Definiciones de colores usando secuencias de escape ANSI
const std::string RED = "\033[31m";   // Rojo para la información del paciente
const std::string GREEN = "\033[32m"; // Verde para la información adicional
const std::string BLUE = "\033[34m";  // Azul para la información de la imagen
const std::string RESET = "\033[0m";  // Restablecer al color predeterminado

void readString(ifstream& inFile, string& str) {
    size_t length;
    inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
    str.resize(length);
    inFile.read(&str[0], length);
}

void readPatient(ifstream& inFile, Patient& patient) {
    readString(inFile, patient.name);
    readString(inFile, patient.lastName);
    inFile.read(reinterpret_cast<char*>(&patient.age), sizeof(patient.age));
    readString(inFile, patient.gender);
    readString(inFile, patient.dateOfBirth);
    readString(inFile, patient.address);
    readString(inFile, patient.phone);
    readString(inFile, patient.email);
    readString(inFile, patient.bloodType);
    readString(inFile, patient.allergies);
    readString(inFile, patient.diseases);
    readString(inFile, patient.surgeries);
    readString(inFile, patient.observations);
}

void readImage(ifstream& inFile, Image& image) {
    readString(inFile, image.name);
    readString(inFile, image.type);
    inFile.read(reinterpret_cast<char*>(&image.width), sizeof(image.width));
    inFile.read(reinterpret_cast<char*>(&image.height), sizeof(image.height));
    readString(inFile, image.weight);
}

void readHeader(ifstream& inFile, FileHeader& header) {
    readString(inFile, header.fileType);
    readString(inFile, header.version);
    readString(inFile, header.creation_date);
    readPatient(inFile, header.patient);
    readImage(inFile, header.image);
}


void printPatient(const Patient &patient)
{
    std::cout << GREEN; // Cambiar color a verde
    std::cout << "Nombre: " << patient.name << "\n";
    std::cout << "Apellido: " << patient.lastName << "\n";
    std::cout << "Edad: " << patient.age << "\n";
    std::cout << "Sexo: " << patient.gender << "\n";
    std::cout << "Fecha de nacimiento: " << patient.dateOfBirth << "\n";
    std::cout << "Dirección: " << patient.address << "\n";
    std::cout << "Teléfono: " << patient.phone << "\n";
    std::cout << "Correo electrónico: " << patient.email << "\n";
    std::cout << "Tipo de sangre: " << patient.bloodType << "\n";
    std::cout << "Alergias: " << patient.allergies << "\n";
    std::cout << "Enfermedades: " << patient.diseases << "\n";
    std::cout << "Cirugías: " << patient.surgeries << "\n";
    std::cout << "Observaciones: " << patient.observations << "\n";
    std::cout << RESET; // Restablecer el color al predeterminado
}

void printImage(const Image &image)
{
    std::cout << BLUE; // Cambiar color a azul
    std::cout << "Nombre de la imagen: " << image.name << "\n";
    std::cout << "Tipo: " << image.type << "\n";
    std::cout << "Ancho: " << image.width << "\n";
    std::cout << "Alto: " << image.height << "\n";
    std::cout << "Peso: " << image.weight << " bytes\n";
    std::cout << RESET; // Restablecer el color al predeterminado
}