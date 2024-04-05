#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void pruebaVerMatriz(imagen) {
    Mat image = imread(imagen, IMREAD_COLOR);

    // Verifica si la imagen se cargó correctamente
    if(image.empty()) {
        cout << "Error al cargar la imagen." << endl;
        return -1;
    }

    // Muestra las dimensiones de la imagen
    cout << "Dimensiones de la imagen: " << image.rows << "x" << image.cols << endl;

    // Convierte la imagen a matriz
    Mat matriz;
    cvtColor(image, matriz, COLOR_BGR2GRAY); // Convierte a escala de grises para simplificar la matriz

    // Imprime la matriz (opcional)
    cout << "Matriz resultante: " << endl << matriz << endl;
}
