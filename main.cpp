#include <iostream>
#include "Examples.hh"



int main(int argc, char *argv[]) {



//    crossKernel();
    Image loaded = Image::fromPPM(argv[1], Image::ImportType::BINARY);

    //    Image padded = Image::addPadding(loaded, 10, 255);
    auto ker = Morphology::kerSquare(3);
    auto iterations = 1;
//    std::cout << "Image size: " << loaded.getWidth() << "x" << loaded.getHeight() << " -- Kernel: Circle of size 5 "
//              << " -- Iterations: " << iterations << std::endl;
//    Examples::benchErode(loaded, ker, iterations).writePPM("erosion.ppm");;
    Examples::benchDilate(loaded, ker, iterations).writePPM("dilation.ppm");
//    Examples::benchOpen(padded, ker, iterations);
//    Examples::benchClose(padded, ker, iterations);

    return 0;
}