    #ifndef EDGE_DETECTOR_H
    #define EDGE_DETECTOR_H

    #include "ImageMatrix.h"
    #include "Convolution.h"
    #include <vector>

    class EdgeDetector {
        public:
            EdgeDetector(); 
            ~EdgeDetector();
            ImageMatrix getDerivativeApproximation(const ImageMatrix& input_image, bool vertical);
            double calculateGradientMagnitude(double verticalPixel, double horizontalPixel);
            double calculateEdgeThreshold(ImageMatrix& Ix, ImageMatrix& Iy);
            void deleteSobelOperators();

            std::vector<std::pair<int, int>> detectEdges(const ImageMatrix& input_image);

        private:
            double** sobelOperatorX;
            double** sobelOperatorY;
            // add your private member variables and functions 
    };

    #endif // EDGE_DETECTOR_H


