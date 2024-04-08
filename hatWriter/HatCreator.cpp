#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include "FileHeader.h"

int main() {
    // Crear un archivo .hat
    std::ofstream outFile("radiography.hat", std::ios::binary);
    if (!outFile) {
        std::cerr << "Error al crear el archivo" << std::endl;
        return 1;
    }
    
    Patient patient = {
        "Juan",
        "Perez",
        25,
        "M",
        "1996-01-01",
        "Calle 123",
        "123456789",
        "juan@gmail.com",
        "O+",
        "Ninguna",
        "Ninguna",
        "Ninguna",
        "Ninguna"
    };

    Image image = {
        "Radiografia",
        "jpg",
        255,
        255
    };

    // Configurar la cabecera
    FileHeader header = {
        "HAT",
        "1.0",
        "2024-10-01",
        patient,
        image
    };

    // Escribir la cabecera en el archivo
    outFile.write((char*)&header, sizeof(header));

    outFile.write("waos", 8); // Escribir una cadena de caracteres
    // Cerrar el archivo
    outFile.close();
    std::cout << "Archivo 'radiography.hat' creado exitosamente." << std::endl;

    return 0;
}
