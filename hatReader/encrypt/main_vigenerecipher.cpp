// main.cpp
#include "VigenereCipher.h"
#include "main_vigenerecipher.h"
#include <fstream>
#include <iostream>
#include <string>

int vigenereExec(std::string mode, std::string key, std::string inputFile, std::string outputFile) {

    std::ifstream input(inputFile);
    if (!input) {
        std::cerr << "Error: No se puede abrir el archivo de entrada.\n";
        return 1;
    }

    std::ofstream output(outputFile);
    if (!output) {
        std::cerr << "Error: No se puede abrir el archivo de salida.\n";
        return 1;
    }

    VigenereCipher cipher(key);
    std::string line;
    if (mode == "e") { //encriptar
        while (getline(input, line)) {
            output << cipher.encrypt(line) << '\n';
        }
    } else if (mode == "d") { //desencriptar
        while (getline(input, line)) {
            output << cipher.decrypt(line) << '\n';
        }
    } else {
        std::cerr << "Error: Modo inválido. Use '(e)ncriptar' o '(d)esencriptar''.\n";
        return 1;
    }

    input.close();
    output.close();
    return 0;
}
