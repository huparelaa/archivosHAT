#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cstring>
#include "./header/FileHeader.h"
#include <string>
#include "./imageBody/Body.h"
#include "./encrypt/main_vigenerecipher.h"
#include <opencv2/opencv.hpp>

using namespace std;
std::string SECRET_KEY = "123";
std::string getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now_time));
    return std::string(buf);
}

int main() {
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

    FileHeader header = {
        "HAT",
        "1.0",
        getCurrentDate(), // Obtener la fecha dinámicamente
        patient,
        image
    };
    
    std::string key = "F#45F/331.h"; // Clave para cifrar la cabecera
    writeHeader(outFile, header, key);

    Mat matriz = generarMatrizApartirDeImagen("static/6ta.jpg");
    outFile.write((char*)matriz.data, matriz.total() * matriz.elemSize());
    outFile.close();
    std::cout << "Archivo 'radiography.hat' creado exitosamente." << std::endl;
    return 0;
}
