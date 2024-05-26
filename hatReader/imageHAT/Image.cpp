#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

Mat swapHalves(const Mat& image);

void readImageAndShow(int ancho, int alto, int tipo) {
    ifstream inFile("../hat/radiography.hat", ios::binary);
    if (!inFile) {
        cerr << "Error al abrir el archivo" << endl;
    }

    // Calcular el tamaño del buffer basado en las dimensiones y el tipo de datos
    size_t bufferSize = ancho * alto * CV_MAT_CN(tipo);
    vector<uchar> buffer(bufferSize);

    // Leer los datos de la matriz en el buffer
    inFile.read(reinterpret_cast<char*>(buffer.data()), bufferSize);
    if (!inFile) {
        cerr << "Error leyendo el contenido de la matriz del archivo" << endl;
    }

    // Reconstruir la matriz a partir del buffer
    Mat matriz(alto, ancho, tipo, buffer.data());
    matriz = swapHalves(matriz);

    namedWindow("Imagen", WINDOW_AUTOSIZE);

    imshow("Imagen", matriz);

    waitKey(0);
    inFile.close();
}

// transform to function
Mat swapHalves(const Mat& image) {
    int halfWidth = image.cols / 2;
    Mat leftHalf(image, Rect(0, 0, halfWidth, image.rows));
    Mat rightHalf(image, Rect(halfWidth, 0, halfWidth, image.rows));
    
    // Crear una nueva imagen donde colocaremos las mitades intercambiadas
    Mat correctedImage(image.rows, image.cols, image.type());

    // Colocar la mitad derecha en el lado izquierdo de la imagen corregida
    rightHalf.copyTo(correctedImage(Rect(0, 0, halfWidth, image.rows)));

    // Colocar la mitad izquierda en el lado derecho de la imagen corregida
    leftHalf.copyTo(correctedImage(Rect(halfWidth, 0, halfWidth, image.rows)));

    return correctedImage;
}