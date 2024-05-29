#include <iostream>
#include <fstream>
#include "./header/FileHeader.h"
#include "./encrypt/VigenereCipher.h"
#include "./compress/LZW.h"
#include <opencv2/opencv.hpp>
#include "./imageHAT/Image.h"
using namespace cv;
using namespace std;

const std::string RESET = "\033[0m";  // Restablecer al color predeterminado

void readHeaderAndDecrypt(ifstream &inFile, FileHeader &header, const std::string &key) {
    // Leer el tamaño de la cabecera comprimida
    size_t compressedSize;
    inFile.read(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize));

    // Leer la cabecera comprimida
    std::vector<int> compressedHeader(compressedSize);
    for (size_t i = 0; i < compressedSize; ++i) {
        inFile.read(reinterpret_cast<char*>(&compressedHeader[i]), sizeof(compressedHeader[i]));
    }

    // Descomprimir la cabecera
    LZW lzw;
    std::string encryptedHeader = lzw.decompress(compressedHeader);

    // Desencriptar la cabecera
    VigenereCipher cipher(key);
    std::string decryptedHeader = cipher.decrypt(encryptedHeader);

    // Convertir la cabecera desencriptada a un stream
    std::istringstream decryptedHeaderStream(decryptedHeader);

    // Leer la cabecera desde el stream desencriptado
    readString(decryptedHeaderStream, header.fileType);
    readString(decryptedHeaderStream, header.version);
    readString(decryptedHeaderStream, header.creation_date);
    readPatient(decryptedHeaderStream, header.patient);
    readImage(decryptedHeaderStream, header.image);
}

int main()
{
    std::ifstream inFile("../hat/radiography.hat", std::ios::binary);
    if (!inFile)
    {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return 1;
    }

    // Leer y desencriptar la cabecera
    FileHeader header;
    std::string key = "F#45F/331.h"; // Clave para desencriptar la cabecera
    readHeaderAndDecrypt(inFile, header, key);
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

    std::cout << RESET; // Restablecer al color predeterminado

    int ancho = header.image.width;
    int alto = header.image.height;
    int tipo = CV_8UC1;
    readImageAndShow(ancho, alto, tipo);

    // Cerrar el archivo
    inFile.close();

    return 0;
}
