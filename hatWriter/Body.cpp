#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat generarMatrizApartirDeImagen(const string& imagen) {
    Mat image = imread(imagen, IMREAD_COLOR);
    Mat matriz;

    // Verifica si la imagen se cargó correctamente
    if(image.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return matriz; // Devuelve una matriz vacía si hay un error
    }

    // Muestra las dimensiones de la imagen
    cout << "Dimensiones de la imagen: " << image.rows << "x" << image.cols << endl;

    // Convierte la imagen a matriz
    cvtColor(image, matriz, COLOR_BGR2GRAY); // Convierte a escala de grises para simplificar la matriz

    return matriz; // Devuelve la matriz
}
