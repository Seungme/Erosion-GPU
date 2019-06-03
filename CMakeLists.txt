cmake_minimum_required(VERSION 3.14)
project(Erosion_GPU)

set(CMAKE_CXX_STANDARD 17)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -m64 -march=native -fopt-info-vec-optimized -O3" )

add_executable(Erosion_GPU main.cpp Image/Image.cpp Image/Image.hh CPU/Morphology.cpp CPU/Morphology.hh Chronometer.cpp Chronometer.hh Examples.cpp Examples.hh)