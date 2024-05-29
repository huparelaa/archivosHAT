#ifndef FILEHEADER_H
#define FILEHEADER_H
#include <string>
#include <fstream>

struct Patient
{
    std::string name;
    std::string lastName;
    int age;
    std::string gender;
    std::string dateOfBirth;
    std::string address;
    std::string phone;
    std::string email;
    std::string bloodType;
    std::string allergies;
    std::string diseases;
    std::string surgeries;
    std::string observations;
};

struct Image
{
    std::string name;
    std::string type;
    int width;
    int height;
    std::string weight;
};

struct FileHeader
{
    std::string fileType;
    std::string version;
    std::string creation_date;
    Patient patient;
    Image image;
};

Patient getPatientData();
Image createImageFromPath(std::string path);

void writeString(std::ofstream& outFile, const std::string& str);
void writePatient(std::ofstream& outFile, const Patient& patient);
void writeImage(std::ofstream& outFile, const Image& image);
void writeHeader(std::ofstream &outFile, const FileHeader &header, const std::string &key);

#endif
