#include <iostream>
#include "Examples.hh"



int main() {



//    crossKernel();
    Image loaded = Image::fromPPM("../Data/RealSnake.ppm", Image::ImportType::BINARY);
    Examples::complexImage(loaded, 2);

    return 0;
}