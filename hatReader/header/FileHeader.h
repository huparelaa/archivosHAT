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

void readString(std::ifstream& inFile, std::string& str);
void readPatient(std::ifstream& inFile, Patient& patient);
void readImage(std::ifstream& inFile, Image& image);
void readHeader(std::ifstream& inFile, FileHeader& header);
void printPatient(const Patient &patient);
void printImage(const Image &image);

#endif
