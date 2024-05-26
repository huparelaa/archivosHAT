#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat generarMatrizApartiDeImagen(const string& imagen) {
    Mat image = imread(imagen, IMREAD_COLOR);
    Mat matriz;

    if(image.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return matriz; // Devuelve una matriz vacía si hay un error
    }

    cout << "Dimensiones de la imagen: " << image.rows << "x" << image.cols << endl;

    // Convierte la imagen a matriz
    cvtColor(image, matriz, COLOR_BGR2GRAY); // Convierte a escala de grises para simplificar la matriz

    cout << "Matriz resultante: " << endl << matriz << endl;

    return matriz; // Devuelve la matriz
}

void generarImagenApartirDeMatriz(const Mat& matriz, const string& nombreArchivo) {

    Mat imagen(matriz.rows, matriz.cols, CV_8UC1); // CV_8UC1 indica una imagen de 1 canal (escala de grises)
    
    // Copiar los valores de la matriz a la imagen
    matriz.convertTo(imagen, CV_8U); // Convertir la matriz a tipo CV_8U (8 bits sin signo)

    // Guardar la imagen en el archivo especificado
    imwrite(nombreArchivo, imagen);
}