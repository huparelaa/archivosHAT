#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cstring>
#include "FileHeader.h"
#include <string>
#include "Body.h"
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    // Crear un archivo .hat
    std::ofstream outFile("../hat/radiography.hat", std::ios::binary);
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
    // Patient patient = getPatientData();
    
    Image image = createImageFromPath("static/6ta.jpg");

    // Configurar la cabecera
    FileHeader header = {
        "HAT",
        "1.0",
        "9-4-2024",
        patient,
        image
    };

    // Escribir la cabecera en el archivo
    outFile.write((char*)&header, sizeof(header));
    Mat matriz = generarMatrizApartirDeImagen("static/6ta.jpg");
    outFile.write((char*)matriz.data, matriz.total() * matriz.elemSize());
    // Cerrar el archivo
    outFile.close();
    std::cout << "Archivo 'radiography.hat' creado exitosamente." << std::endl;

    return 0;
}
