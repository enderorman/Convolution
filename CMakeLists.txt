cmake_minimum_required(VERSION 3.20)
project(Assignment1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment1 src/Convolution.cpp src/DecodeMessage.cpp src/EdgeDetector.cpp src/EncodeMessage.cpp
                src/ImageLoader.cpp src/ImageMatrix.cpp src/ImageProcessor.cpp src/ImageSharpening.cpp src/main.cpp)
