#include <iostream>
#include "Examples.hh"

enum class kerShape : int {
    SQUARE = 0,
    CIRCLE = 1
};

int main(int argc, char *argv[]) {

    // default values
    kerShape shape = kerShape::SQUARE;
    unsigned kerSize = 3;

    if (argc < 2 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " INPUT_IMAGE [KERNEL_SIZE] [KERNEL_SHAPE]." << std::endl << "       With KERNEL_SHAPE = {'square' (default), 'circle'}" << std::endl;
        return 1;
    }
    if (argc >= 3) {
        kerSize = atoi(argv[2]);
    }
    if (argc == 4) {
        if (std::string(argv[3]) == "square")
            shape = kerShape::SQUARE;
        else if (std::string(argv[3]) == "circle")
            shape = kerShape::CIRCLE;
    }

    std::vector<std::vector<unsigned char>> ker;
    switch (shape) {
        case kerShape::SQUARE:
            ker = Morphology::kerSquare(kerSize);
            break;
        case kerShape::CIRCLE:
            ker = Morphology::kerCircle(kerSize);
            break;
    }

    Image loaded = Image::fromPPM(argv[1], Image::ImportType::GRAY);

    //    Image padded = Image::addPadding(loaded, 10, 255);
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