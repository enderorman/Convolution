// Convolution.h

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "ImageMatrix.h"

// Class `Convolution`: Provides the functionality to convolve an image with
// a kernel. Padding is a bool variable, indicating whether to use zero padding or not.
class Convolution {
public:
    // Constructors and destructors
    Convolution(); // Default constructor
    Convolution(double** customKernel, int kernelHeight, int kernelWidth, int stride, bool padding); // Parametrized constructor for custom kernel and other parameters
    ~Convolution(); // Destructor

    Convolution(const Convolution &other); // Copy constructor
    Convolution& operator=(const Convolution &other); // Copy assignment operator

    ImageMatrix convolve(const ImageMatrix& input_image) const; // Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
    double** getKernel() const;
    ImageMatrix getPaddedImage(const ImageMatrix& input_image) const;
    bool checkIndexIsOutOfBonds(int height, int width, int i, int j) const;
    int calculateOutputHeight(int inputHeight) const;
    int calculateOutputWidth(int inputWidth) const;
    ImageMatrix getConvolvedImage(const ImageMatrix& input_image, int outputHeight, int outputWidth) const;
    void deleteKernel();
    int kernelHeight, kernelWidth, stride;
    bool padding;
private:
    // Add any private member variables and functions .
    double** kernel;
};

#endif // CONVOLUTION_H
