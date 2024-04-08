#include <iostream>
#include <fstream>
#include "FileHeader.h" // Asegúrate de que esta ruta sea correcta

void printPatient(const Patient& patient) {
    std::cout << "Nombre: " << patient.name << "\n";
    std::cout << "Apellido: " << patient.lastName << "\n";
    // Agrega el resto de los campos si lo deseas
}

void printImage(const Image& image) {
    std::cout << "Nombre de la imagen: " << image.name << "\n";
    std::cout << "Tipo: " << image.type << "\n";
    // Agrega el resto de los campos si lo deseas
}

int main() {
    std::ifstream inFile("radiography.hat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return 1;
    }

    // Leer la cabecera
    FileHeader header;
    inFile.read((char*)&header, sizeof(header));
    if (!inFile) {
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

    // Leer el contenido adicional
    char content[9] = {}; // Un byte más para el carácter nulo
    inFile.read(content, 8); // asumiendo que sabes la longitud del contenido adicional
    if (!inFile) {
        std::cerr << "Error leyendo el contenido del archivo" << std::endl;
        return 1;
    }

    std::cout << "Contenido adicional: " << content << std::endl;

    // Cerrar el archivo
    inFile.close();

    return 0;
}
