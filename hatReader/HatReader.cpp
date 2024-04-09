#include <iostream>
#include <fstream>
#include "FileHeader.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Image.h"

using namespace cv;
using namespace std;

// Definiciones de colores usando secuencias de escape ANSI
const std::string RED = "\033[31m";   // Rojo para la información del paciente
const std::string GREEN = "\033[32m"; // Verde para la información adicional
const std::string BLUE = "\033[34m";  // Azul para la información de la imagen
const std::string RESET = "\033[0m";  // Restablecer al color predeterminado

void printPatient(const Patient &patient)
{
    std::cout << GREEN; // Cambiar color a rojo
    std::cout << "Nombre: " << patient.name << "\n";
    std::cout << "Apellido: " << patient.lastName << "\n";
    std::cout << "Edad: " << patient.age << "\n";
    std::cout << "Sexo: " << patient.gender << "\n"; // Asegúrate de completar esta línea correctamente
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
    std::cout << "Peso: " << image.weight << "bytes"
              << "\n";
    std::cout << RESET; // Restablecer el color al predeterminado
}

int main()
{
    std::ifstream inFile("../hat/radiography.hat", std::ios::binary);
    if (!inFile)
    {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return 1;
    }

    // Leer la cabecera
    FileHeader header;
    inFile.read((char *)&header, sizeof(header));
    if (!inFile)
    {
        std::cerr << "Error leyendo la cabecera del archivo" << std::endl;
        return 1;
    }

    // Imprimir los detalles de la cabecera
    std::cout << "Cabecera del archivo:\n";
    std::cout << "Tipo de archivo: " << header.fileType << "\n";
    std::cout << "Versión: " << header.version << "\n";
    std::cout << "Fecha de creación: " << header.creation_date << "\n";

    // Imprimir los detalles del paciente y la imagen
    printPatient(header.patient);
    printImage(header.image);

    // Calcular el tamaño del contenido adicional
    inFile.seekg(0, ios::end); // Mover al final del archivo
    auto endPos = inFile.tellg();
    auto contentSize = static_cast<size_t>(endPos) - sizeof(header);
    inFile.seekg(sizeof(header), ios::beg);  
    
    // Leer el contenido adicional
    vector<char> content(contentSize);
    inFile.read(content.data(), contentSize);
    if (!inFile)
    {
        cerr << "Error leyendo el contenido adicional del archivo" << endl;
        return 1;
    }
    std::cout << RESET; // Restablecer el color al predeterminado

    int ancho = header.image.width;
    int alto = header.image.height;
    int tipo = CV_8UC1;
    readImageAndShow(ancho, alto, tipo);
    // Cerrar el archivo
    inFile.close();

    return 0;
}
