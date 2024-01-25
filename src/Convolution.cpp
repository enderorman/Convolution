#include "Convolution.h"
// Default constructor
Convolution::Convolution() {

}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){
    kernelHeight = kh;
    kernelWidth = kw;
    stride = stride_val;
    padding = pad;
    kernel = new double*[kh];
    for (int i = 0; i < kernelHeight; ++i) {
        kernel[i] = new double[kw];
        for (int j = 0; j < kernelWidth; ++j) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    deleteKernel();
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    kernel = new double*[kernelHeight];
    padding = other.padding;
    stride = other.stride;
    for (int i = 0; i < kernelHeight; i++){
        kernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; j++){
            kernel[i][j] = other.getKernel()[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other){
        return *this;
    }
    deleteKernel();
    if (other.kernel != nullptr){
        kernelHeight = other.kernelHeight;
        kernelWidth = other.kernelWidth;
        kernel = new double*[kernelHeight];
        for (int i = 0; i < kernelHeight; i++){
            kernel[i] = new double[kernelWidth];
        }
        for (int i = 0; i < kernelHeight; i++) {
            for (int j = 0; j < kernelWidth; j++) {
                kernel[i][j] = other.getKernel()[i][j];
            }
        }
    }
    else{
        kernel = nullptr;
        kernelHeight = 0;
        kernelWidth = 0;
    }
    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    double** paddedData;
    double** outputMatrix;
    int height = input_image.get_height(), width = input_image.get_width();
    int outputHeight = calculateOutputHeight(height), outputWidth = calculateOutputWidth(width);
    if (padding){
        ImageMatrix paddedInputImage = getPaddedImage(input_image);
        return getConvolvedImage(paddedInputImage, outputHeight, outputWidth);
    }
    else{
        return getConvolvedImage(input_image, outputHeight, outputWidth);
    }
}

ImageMatrix Convolution::getConvolvedImage(const ImageMatrix& input_image, int outputHeight, int outputWidth) const{
    ImageMatrix outputImage(outputHeight, outputWidth);
    for (int i = 0; i < outputHeight; i++){
        for (int j = 0; j < outputWidth; j++){
            int windowStartRow = i * stride;
            int windowStartCol = j * stride;
            double sum = 0;
            for (int m = 0; m < kernelHeight; m++){
                for (int n = 0; n < kernelWidth; n++){
                    int inputRow = windowStartRow + m;
                    int inputCol = windowStartCol + n;
                    sum += input_image.get_data(inputRow, inputCol) * kernel[m][n];
                    }
            }
                outputImage.get_data()[i][j] = sum;
            }
        }
    return  outputImage;
    }

bool Convolution::checkIndexIsOutOfBonds(int height, int width, int i, int j) const {
    if (i == 0 || i == height - 1 || j == 0 || j == width - 1){
        return true;
    }
    return false;
}

int Convolution::calculateOutputHeight(int inputHeight) const{
    return ((inputHeight - kernelHeight + 2 * padding) / stride) + 1;
}

int Convolution::calculateOutputWidth(int inputWidth) const{
    return ((inputWidth - kernelWidth + 2 * padding) / stride) + 1;
}

double **Convolution::getKernel() const {
    return kernel;
}

ImageMatrix Convolution::getPaddedImage(const ImageMatrix &input_image) const {
    int newHeight = input_image.get_height() + 2, newWidth = input_image.get_width() + 2;
    ImageMatrix paddedImage(newHeight, newWidth);
    for (int i = 0; i < newHeight; i++){
        for (int j = 0; j < newWidth; j++){
            if (checkIndexIsOutOfBonds(newHeight, newWidth, i, j)){
                paddedImage.get_data()[i][j] = 0;
            }
            else{
                paddedImage.get_data()[i][j] = input_image.get_data(i - 1, j - 1);
            }
        }
    }
    return paddedImage;
}


void Convolution::deleteKernel(){
    if (kernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }
}




