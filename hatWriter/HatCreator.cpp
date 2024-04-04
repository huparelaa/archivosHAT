#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

struct FileHeader {
    char fileType[4] = "HAT";
    int version = 1;
    int headerSize = sizeof(FileHeader);
    // patient info
    int patientInfoSize = sizeof(Patient);
    // image info
    int imageInfoSize = sizeof(Image);

    int numberOfElements = 10;
    time_t creationDate;
};

// Patient info
struct Patient {
    char name[50];
    char lastName[50];
};

// Image info
struct Image {
    char name[50];
    char path[100];
    char type[10];
    int width;
    int height;
    int depth;
    int channels;
    int bitsPerPixel;
    int size;
    char date[20];
    char time[20];
    char description[100];
};

int main() {
    // Crear un archivo .hat
    std::ofstream outFile("example.hat", std::ios::binary);
    if (!outFile) {
        std::cerr << "Error al crear el archivo" << std::endl;
        return 1;
    }

    // Configurar la cabecera
    FileHeader header;
    // Establecer la fecha de creación como el tiempo actual
    header.creationDate = std::time(nullptr);

    // Escribir la cabecera en el archivo
    outFile.write((char*)&header, sizeof(header));

    // Simular algunos datos para escribir en el archivo
    // Por ejemplo, escribir números del 1 al 10
    for (int i = 1; i <= header.numberOfElements; ++i) {
        outFile.write((char*)&i, sizeof(i));
    }
    outFile.write("waos", 8); // Escribir una cadena de caracteres
    // Cerrar el archivo
    outFile.close();
    std::cout << "Archivo 'example.hat' creado exitosamente." << std::endl;

    return 0;
}
