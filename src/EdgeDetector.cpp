// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include <cmath>
#include "iostream"
// Default constructor
EdgeDetector::EdgeDetector() {
    sobelOperatorX = new double *[3]{
            new double[3]{-1.0, 0, 1.0},
            new double[3]{-2.0, 0, 2.0},
            new double[3]{-1.0, 0, 1.0}};
    sobelOperatorY = new double *[3]{
            new double[3]{-1.0, -2.0, -1.0},
            new double[3]{0, 0, 0},
            new double[3]{1, 2, 1}
    };
}

// Destructor
EdgeDetector::~EdgeDetector() {
    deleteSobelOperators();
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    ImageMatrix Ix = getDerivativeApproximation(input_image, true);
    ImageMatrix Iy = getDerivativeApproximation(input_image, false);
    double edgeThreshold = calculateEdgeThreshold(Ix, Iy);
    int height = input_image.get_height(), width = input_image.get_width();
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            double verticalPixel = Ix.get_data(i, j), horizontalPixel = Iy.get_data(i, j);
            if (calculateGradientMagnitude(verticalPixel, horizontalPixel) > edgeThreshold){
                edges.push_back(std::make_pair(i, j));
            }
        }
    }
    return edges;
}

ImageMatrix EdgeDetector::getDerivativeApproximation(const ImageMatrix& input_image, bool vertical){
    double** sobelOperator = (vertical? sobelOperatorX:sobelOperatorY);
    Convolution convolutionHelper(sobelOperator, 3, 3, 1, true);
    ImageMatrix derivativeApproximation = convolutionHelper.convolve(input_image);
    return derivativeApproximation;
}

double EdgeDetector::calculateGradientMagnitude(double verticalPixel, double horizontalPixel){
    return sqrt((verticalPixel * verticalPixel) + (horizontalPixel * horizontalPixel));
}

double EdgeDetector::calculateEdgeThreshold(ImageMatrix& Ix, ImageMatrix& Iy){
    double edgeThreshold = 0;
    int height = Ix.get_height(), width = Ix.get_width();
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            edgeThreshold += calculateGradientMagnitude(Ix.get_data(i, j), Iy.get_data(i, j));
        }
    }
    edgeThreshold /= (height * width);
    return edgeThreshold;
}

void EdgeDetector::deleteSobelOperators(){
    for (int i = 0; i < 3; i++){
        delete[] sobelOperatorX[i];
    }
    delete[] sobelOperatorX;

    for (int i = 0; i < 3; i++){
        delete[] sobelOperatorY[i];
    }
    delete[] sobelOperatorY;

}



