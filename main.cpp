#include <iostream>
#include "Examples.hh"



int main(int argc, char *argv[]) {



//    crossKernel();
    Image loaded = Image::fromPPM(argv[1], Image::ImportType::GRAY);

    //    Image padded = Image::addPadding(loaded, 10, 255);
    auto ker = Morphology::kerSquare(atoi(argv[2]));
    auto iterations = 1;
//    std::cout << "Image size: " << loaded.getWidth() << "x" << loaded.getHeight() << " -- Kernel: Circle of size 5 "
//              << " -- Iterations: " << iterations << std::endl;
    Examples::benchErode(loaded, ker, iterations).writePPM("CPUErode.ppm");
    Examples::benchDilate(loaded, ker, iterations).writePPM("CPUDilate.ppm");
//    Examples::benchOpen(loaded, ker, iterations).writePPM("opening.ppm");
//    Examples::benchClose(loaded, ker, iterations).writePPM("closing.ppm");
    loaded.writePPM("original.ppm");

    return 0;
}