cmake_minimum_required(VERSION 3.14)
project(Erosion_GPU)

set(CMAKE_CXX_STANDARD 17)

add_executable(Erosion_GPU main.cpp Image/Image.cpp Image/Image.hh CPU/Morphology.cpp CPU/Morphology.hh Chronometer.cpp Chronometer.hh Examples.cpp Examples.hh)