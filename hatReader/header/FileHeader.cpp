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

void readString(istream& in, string& str) {
    size_t length;
    in.read(reinterpret_cast<char*>(&length), sizeof(length));
    str.resize(length);
    in.read(&str[0], length);
}

void readPatient(istream& in, Patient& patient) {
    readString(in, patient.name);
    readString(in, patient.lastName);
    in.read(reinterpret_cast<char*>(&patient.age), sizeof(patient.age));
    readString(in, patient.gender);
    readString(in, patient.dateOfBirth);
    readString(in, patient.address);
    readString(in, patient.phone);
    readString(in, patient.email);
    readString(in, patient.bloodType);
    readString(in, patient.allergies);
    readString(in, patient.diseases);
    readString(in, patient.surgeries);
    readString(in, patient.observations);
}

void readImage(istream& in, Image& image) {
    readString(in, image.name);
    readString(in, image.type);
    in.read(reinterpret_cast<char*>(&image.width), sizeof(image.width));
    in.read(reinterpret_cast<char*>(&image.height), sizeof(image.height));
    readString(in, image.weight);
}

void readHeader(istream& in, FileHeader& header) {
    readString(in, header.fileType);
    readString(in, header.version);
    readString(in, header.creation_date);
    readPatient(in, header.patient);
    readImage(in, header.image);
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
    std::cout << RESET; // Restablecer al color predeterminado
}

void printImage(const Image &image)
{
    std::cout << BLUE; // Cambiar color a azul
    std::cout << "Nombre de la imagen: " << image.name << "\n";
    std::cout << "Tipo de imagen: " << image.type << "\n";
    std::cout << "Ancho: " << image.width << "\n";
    std::cout << "Alto: " << image.height << "\n";
    std::cout << "Peso: " << image.weight << "\n";
    std::cout << RESET; // Restablecer al color predeterminado
}
