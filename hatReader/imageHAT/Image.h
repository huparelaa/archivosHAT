#ifndef IMAGE_H 
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

Mat swapHalves(const Mat& image);
void readImageAndShow(int ancho, int alto, int tipo);

#endif // IMAGE_H