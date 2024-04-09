#include <iostream>
#include <string>
#include <fstream> 
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Image {
private:
    string name;
    string type;
    int width;
    int height;
    string weight;

public:
    // Constructor
    Image(string n, string t, int w, int h, string wt) {
        name = n;
        type = t;
        width = w;
        height = h;
        weight = wt;
    }

    // Funciones get para cada característica
    string getName() {
        return name;
    }

    void setName(string n) {
        name = n;
    }

    string getType() {
        return type;
    }

    void setType(string t) {
        type = t;
    }

    int getWidth() {
        return width;
    }

    void setWidth(int w) {
        width = w;
    }

    int getHeight() {
        return height;
    }

    void setHeight(int h) {
        height = h;
    }

    string getWeight() {
        return weight;
    }

    void setWeight(string wt) {
        weight = wt;
    }
};

Image createImageFromPath(string imagePath) {
    Mat image = imread(imagePath);

    if (image.empty()) {
        cerr << "Error al cargar la imagen." << endl;
        exit(EXIT_FAILURE);
    }

    string name = imagePath.substr(imagePath.find_last_of("/\\") + 1);
    string type = imagePath.substr(imagePath.find_last_of(".") + 1);

    int width = image.cols;
    int height = image.rows;

    // Obtener el tamaño del archivo
    ifstream file(imagePath, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        exit(EXIT_FAILURE);
    }
    string weight = to_string(file.tellg());

    return Image(name, type, width, height, weight);
}