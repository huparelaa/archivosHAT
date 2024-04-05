#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat pruebaVerMatriz(const string& imagen) {
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

    // Imprime la matriz (opcional)
    cout << "Matriz resultante: " << endl << matriz << endl;

    return matriz; // Devuelve la matriz
}

void generarImagenAPartirDeMatriz(const Mat& matriz, const string& nombreArchivo) {
    // Crear una imagen a partir de la matriz
    Mat imagen(matriz.rows, matriz.cols, CV_8UC1); // CV_8UC1 indica una imagen de 1 canal (escala de grises)
    
    // Copiar los valores de la matriz a la imagen
    matriz.convertTo(imagen, CV_8U); // Convertir la matriz a tipo CV_8U (8 bits sin signo)

    // Guardar la imagen en el archivo especificado
    imwrite(nombreArchivo, imagen);
}

int main() {
    // Definir una matriz de ejemplo

    Mat matriz = pruebaVerMatriz("6ta.jpg");
    
    // Llamar a la función para generar la imagen a partir de la matriz
    generarImagenAPartirDeMatriz(matriz, "imagen_generada.jpg");
    
    cout << "Imagen generada correctamente." << endl;

    return 0;
}