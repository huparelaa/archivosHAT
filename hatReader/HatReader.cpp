#include <iostream>
#include <fstream>
#include "./header/FileHeader.h"
#include <opencv2/opencv.hpp>
#include "./imageHAT/Image.h"

using namespace cv;
using namespace std;

const std::string RESET = "\033[0m";  // Restablecer al color predeterminado

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
    readHeader(inFile, header);
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

    std::cout << RESET; // Restablecer el color al predeterminado

    int ancho = header.image.width;
    int alto = header.image.height;
    int tipo = CV_8UC1;
    readImageAndShow(ancho, alto, tipo);

    // Cerrar el archivo
    inFile.close();

    return 0;
}
