#ifndef VISOR_MATRIZ_H
#define VISOR_MATRIZ_H
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class VisorMatrizImg {
private:
    cv::Mat matrizImage;
public:
    // Metodo para convertir una imagen a matriz
    Mat generarMatrizApartiDeImagen(const string& imagen);
    // Método para visualizar la matriz como una imagen
    void generarImagenApartirDeMatriz(const Mat& matriz, const string& nombreArchivo);
};
#endif