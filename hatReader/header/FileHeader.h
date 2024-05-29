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

void readString(std::istream& in, std::string& str);
void readPatient(std::istream& in, Patient& patient);
void readImage(std::istream& in, Image& image);
void readHeader(std::istream& in, FileHeader& header);
void printPatient(const Patient &patient);
void printImage(const Image &image);

#endif
