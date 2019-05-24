//
// Created by revetoon on 5/24/19.
//

#ifndef EROSION_GPU_EXAMPLES_HH
#define EROSION_GPU_EXAMPLES_HH

#include <iostream>
#include "Chronometer.hh"
#include "Image/Image.hh"
#include "CPU/Morphology.hh"

namespace Examples {

    void squareKernel();

    void crossKernel();

    void complexImage(Image &img, unsigned iterations);

    Image benchErode(Image &img, const std::vector<std::vector<unsigned char>> &ker, int iterations);
    Image benchDilate(Image &img, const std::vector<std::vector<unsigned char>> &ker, int iterations);
    Image benchOpen(Image &img, const std::vector<std::vector<unsigned char>> &ker, int iterations);
    Image benchClose(Image &img, const std::vector<std::vector<unsigned char>> &ker, int iterations);
};


#endif //EROSION_GPU_EXAMPLES_HH
