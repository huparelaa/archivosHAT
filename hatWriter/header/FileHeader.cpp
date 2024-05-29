#include "FileHeader.h"
#include "../encrypt/VigenereCipher.h"
#include "../compress/LZW.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

void writeString(ostream &out, const std::string &str)
{
    size_t len = str.length();
    out.write(reinterpret_cast<const char *>(&len), sizeof(len));
    out.write(str.c_str(), len);
}

void writePatient(ostream &out, const Patient &patient)
{
    writeString(out, patient.name);
    writeString(out, patient.lastName);
    out.write(reinterpret_cast<const char *>(&patient.age), sizeof(patient.age));
    writeString(out, patient.gender);
    writeString(out, patient.dateOfBirth);
    writeString(out, patient.address);
    writeString(out, patient.phone);
    writeString(out, patient.email);
    writeString(out, patient.bloodType);
    writeString(out, patient.allergies);
    writeString(out, patient.diseases);
    writeString(out, patient.surgeries);
    writeString(out, patient.observations);
}

void writeImage(ostream &out, const Image &image)
{
    writeString(out, image.name);
    writeString(out, image.type);
    out.write(reinterpret_cast<const char *>(&image.width), sizeof(image.width));
    out.write(reinterpret_cast<const char *>(&image.height), sizeof(image.height));
    writeString(out, image.weight);
}

void writeHeader(ofstream &outFile, const FileHeader &header, const std::string &key)
{
    std::ostringstream headerStream;

    writeString(headerStream, header.fileType);
    writeString(headerStream, header.version);
    writeString(headerStream, header.creation_date);
    writePatient(headerStream, header.patient);
    writeImage(headerStream, header.image);

    std::string headerData = headerStream.str();
    VigenereCipher cipher(key);
    std::string encryptedHeader = cipher.encrypt(headerData);

    LZW lzw;
    std::vector<int> compressedHeader = lzw.compress(encryptedHeader);

    size_t compressedSize = compressedHeader.size();
    outFile.write(reinterpret_cast<const char*>(&compressedSize), sizeof(compressedSize));
    for (int code : compressedHeader) {
        outFile.write(reinterpret_cast<const char*>(&code), sizeof(code));
    }
}
