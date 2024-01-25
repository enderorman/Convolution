#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageMatrix sharpImage = ImageSharpening().sharpen(img, 2.0);
    EdgeDetector edgeDetector = EdgeDetector();
    const std::vector<std::pair<int, int>> edges = edgeDetector.detectEdges(sharpImage);
    DecodeMessage decoder = DecodeMessage();
    std::string message = decoder.decodeFromImage(sharpImage, edges);
    return message;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    EdgeDetector edgeDetector = EdgeDetector();
    ImageMatrix sharpImage = ImageSharpening().sharpen(img, 2);
    std::vector<std::pair<int, int>> edges = edgeDetector.detectEdges(sharpImage);
    EncodeMessage encoder = EncodeMessage();
    ImageMatrix resMatrix = encoder.encodeMessageToImage(img, message, edges);
    return resMatrix;
}
