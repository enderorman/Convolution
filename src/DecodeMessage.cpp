// DecodeMessage.cpp

#include "DecodeMessage.h"

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}

char DecodeMessage::decodeBinaryString(std::string segment){
    int decimalValue = std::stoull(segment, 0, 2);
    if (decimalValue <= 32){
        decimalValue += 33;
    }
    if (decimalValue >= 127){
        decimalValue = 126;
    }
    return char(decimalValue);
}
std::string DecodeMessage::createLsbString(std::vector<int>& lsbList){
    int s = lsbList.size();
    int zeroCount = (7 - (s % 7)) % 7;
    std::string lsbString = "";
    for (int i = 0; i < zeroCount; i++){
        lsbString += "0";
    }
    for (int &i: lsbList){
        lsbString += std::to_string(i);
    }
    return lsbString;
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::vector<int> lsbList;
    std::string message = "";
    for (int edgeIndex = 0; edgeIndex < edgePixels.size(); edgeIndex++){
        std::pair<int, int> edge = edgePixels[edgeIndex];
        int i = edge.first, j = edge.second;
        double pixel = image.get_data(i, j);
        int lsb = (int)pixel % 2;
        lsbList.push_back(lsb);
    }
    std::string lsbString = createLsbString(lsbList);
    for (int i = 0; i + 7 <= lsbString.size(); i += 7){
        std::string segment = lsbString.substr(i, 7);
        char c = decodeBinaryString(segment);
        message += c;
    }
    return message;
}

