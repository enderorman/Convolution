#ifndef ENCODE_MESSAGE_H
#define ENCODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage();
    ~EncodeMessage();
    bool checkIndexIsPrime(int ind);
    long long calculateNthFibonacciNumber(int n);
    int calculatePixelValueAfterEncoding(int pixelValue, int lsb);
    std::vector<int> createSegmentBits(int pixelValue);
    std::string createFibonacciTransformationMessage(const std::string &message);
    std::string createRightCircularShiftedMessage(const std::string &message);
    ImageMatrix encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions);


private:
    // Any private helper functions or variables if necessary

};

#endif // ENCODE_MESSAGE_H
