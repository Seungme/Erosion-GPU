#include <iostream>
#include "Examples.hh"



int main() {



//    crossKernel();
    Image loaded = Image::fromPPM("../Data/RealSnake.ppm", Image::ImportType::BINARY);
    Image padded = Image::addPadding(loaded, 10, 255);
    auto ker = Morphology::kerCircle(5);
    auto iterations = 1;
    std::cout << "Image size: " << loaded.getWidth() << "x" << loaded.getHeight() << " -- Kernel: Circle of size 5 "
              << " -- Iterations: " << iterations << std::endl;
    Examples::benchErode(padded, ker, iterations);
    Examples::benchDilate(padded, ker, iterations);
    Examples::benchOpen(padded, ker, iterations);
    Examples::benchClose(padded, ker, iterations);

    padded.writePPM("padded.ppm");

    return 0;
}