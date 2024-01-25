#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    blurring_kernel = new double*[3]{
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0}};
    kernel_height = 3;
    kernel_width = 3;
}


ImageSharpening::~ImageSharpening(){
    deleteBlurringKernel();
    }

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    ImageMatrix blurredImage = getBlurredImage(input_image);
    int height = input_image.get_height(), width = input_image.get_width();
    ImageMatrix sharpImage = input_image + (input_image  - blurredImage) * k;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            double sharpPixelValue = std::max(0.0, std::min(sharpImage.get_data(i, j), 255.0));
            sharpImage.get_data()[i][j] = sharpPixelValue;
        }
    }
    return sharpImage;
}

ImageMatrix ImageSharpening::getBlurredImage(const ImageMatrix& input_image){
    Convolution convolutionHelper(blurring_kernel, kernel_height, kernel_width, 1, true);
    ImageMatrix blurredImage = convolutionHelper.convolve(input_image);
    return blurredImage;
}

void ImageSharpening::deleteBlurringKernel(){
    for (int i = 0; i < 3; i++){
        delete[] blurring_kernel[i];
    }
    delete[] blurring_kernel;
    blurring_kernel = nullptr;
}

