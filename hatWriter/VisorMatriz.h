#ifndef VISOR_MATRIZ_H
#define VISOR_MATRIZ_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class VisorMatrizImg {
private:
    cv::Mat matrizImage;
public:
    Mat generarMatrizApartiDeImagen(const string& imagen);
    void generarImagenApartirDeMatriz(const Mat& matriz, const string& nombreArchivo);
};
#endif