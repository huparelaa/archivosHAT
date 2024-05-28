#include "FileHeader.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void writeString(ofstream& outFile, const string& str) {
    size_t length = str.length();
    outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
    outFile.write(str.c_str(), length);
}

void readString(ifstream& inFile, string& str) {
    size_t length;
    inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
    str.resize(length);
    inFile.read(&str[0], length);
}

void writePatient(ofstream& outFile, const Patient& patient) {
    writeString(outFile, patient.name);
    writeString(outFile, patient.lastName);
    outFile.write(reinterpret_cast<const char*>(&patient.age), sizeof(patient.age));
    writeString(outFile, patient.gender);
    writeString(outFile, patient.dateOfBirth);
    writeString(outFile, patient.address);
    writeString(outFile, patient.phone);
    writeString(outFile, patient.email);
    writeString(outFile, patient.bloodType);
    writeString(outFile, patient.allergies);
    writeString(outFile, patient.diseases);
    writeString(outFile, patient.surgeries);
    writeString(outFile, patient.observations);
}

void readPatient(ifstream& inFile, Patient& patient) {
    readString(inFile, patient.name);
    readString(inFile, patient.lastName);
    inFile.read(reinterpret_cast<char*>(&patient.age), sizeof(patient.age));
    readString(inFile, patient.gender);
    readString(inFile, patient.dateOfBirth);
    readString(inFile, patient.address);
    readString(inFile, patient.phone);
    readString(inFile, patient.email);
    readString(inFile, patient.bloodType);
    readString(inFile, patient.allergies);
    readString(inFile, patient.diseases);
    readString(inFile, patient.surgeries);
    readString(inFile, patient.observations);
}

void writeImage(ofstream& outFile, const Image& image) {
    writeString(outFile, image.name);
    writeString(outFile, image.type);
    outFile.write(reinterpret_cast<const char*>(&image.width), sizeof(image.width));
    outFile.write(reinterpret_cast<const char*>(&image.height), sizeof(image.height));
    writeString(outFile, image.weight);
}

void readImage(ifstream& inFile, Image& image) {
    readString(inFile, image.name);
    readString(inFile, image.type);
    inFile.read(reinterpret_cast<char*>(&image.width), sizeof(image.width));
    inFile.read(reinterpret_cast<char*>(&image.height), sizeof(image.height));
    readString(inFile, image.weight);
}

void writeHeader(ofstream& outFile, const FileHeader& header) {
    writeString(outFile, header.fileType);
    writeString(outFile, header.version);
    writeString(outFile, header.creation_date);
    writePatient(outFile, header.patient);
    writeImage(outFile, header.image);
}

void readHeader(ifstream& inFile, FileHeader& header) {
    readString(inFile, header.fileType);
    readString(inFile, header.version);
    readString(inFile, header.creation_date);
    readPatient(inFile, header.patient);
    readImage(inFile, header.image);
}
