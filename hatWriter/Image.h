#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>

class Image {
private:
    std::string name;
    std::string type;
    int width;
    int height;
    std::string weight;

public:
    // Constructor
    Image(std::string n, std::string t, int w, int h, std::string wt);

    // Funciones get para cada característica
    std::string getName();
    void setName(std::string n);

    std::string getType();
    void setType(std::string t);

    int getWidth();
    void setWidth(int w);

    int getHeight();
    void setHeight(int h);

    std::string getWeight();
    void setWeight(std::string wt);
};

Image createImageFromPath(std::string imagePath);

#endif // IMAGE_H
