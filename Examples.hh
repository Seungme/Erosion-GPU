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

};


#endif //EROSION_GPU_EXAMPLES_HH
