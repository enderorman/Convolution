#include "EncodeMessage.h"
#include "ImageSharpening.h"
#include <cmath>



// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}


std::vector<int>EncodeMessage::createSegmentBits(int pixelValue){
    std::vector<int> res;
    for (int i = 0; i < 7; i++){
        res.push_back(pixelValue & 1);
        pixelValue >>= 1;
    }
    //std::reverse(res.begin(), res.end());
    return res;
}

bool EncodeMessage::checkIndexIsPrime(int ind){
    if (ind < 2){
        return false;
    }
    if (ind == 2){
        return true;
    }
    for (int i = 2; i * i <= ind; i++){
        if (ind % i == 0){
            return false;
        }
    }
    return true;
}
int EncodeMessage::calculatePixelValueAfterEncoding(int pixelValue, int lsb){
    if (pixelValue % 2 == 0 && lsb){
        pixelValue++;
    }
    if (pixelValue % 2 == 1 && !lsb){
        pixelValue--;
    }
    return pixelValue;
}
long long EncodeMessage::calculateNthFibonacciNumber(int n){
    std::vector<long long>fib(n + 5);
    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i < n + 5; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n];
}
std::string EncodeMessage::createFibonacciTransformationMessage(const std::string &message){
    std::string transformedString;
    for (int i = 0; i < message.size(); i++){
        const char c = message[i];
        if (checkIndexIsPrime(i)){
            long long asciiValue = (int)c + calculateNthFibonacciNumber(i);
            if (asciiValue <= 32){
                asciiValue += 33;
            }
            if(asciiValue >= 127){
                asciiValue = 126;
            }
            transformedString += (char)asciiValue;
        }
        else{
            transformedString += c;
        }
    }
    return transformedString;
}

std::string EncodeMessage::createRightCircularShiftedMessage(const std::string& message){
    int mid = (message.size() + 1) / 2;
    return  message.substr(mid) + message.substr(0, mid);
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    std::string fibonacciTransformationMessage = createFibonacciTransformationMessage(message);
    std::string rightCircularShiftedMessage = createRightCircularShiftedMessage(fibonacciTransformationMessage);
    ImageMatrix resMatrix = img;
    //1010101|100
    for (int edgeIndex = 0; edgeIndex < std::min(positions.size(), rightCircularShiftedMessage.size() * 7); edgeIndex += 7){
        std::vector<int> binarySegment = createSegmentBits((int)rightCircularShiftedMessage[edgeIndex / 7]);
        for (int segmentIndex = edgeIndex; segmentIndex < std::min(edgeIndex + 7, (int)positions.size()); segmentIndex++){
            std::pair<int, int> edge = positions[segmentIndex];
            int i = edge.first, j = edge.second;
            int lsb = binarySegment[segmentIndex % 7];
            int pixelValue = img.get_data(i, j);
            resMatrix.get_data()[i][j] = calculatePixelValueAfterEncoding(pixelValue, lsb);
        }
    }
    return resMatrix;
}

