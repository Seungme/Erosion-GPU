#include <iostream>
#include "Chronometer.hh"
#include "Image/Image.hh"
#include "Morpho/Morphology.hh"

void squareKernel() {
    Chronometer chrono = Chronometer();
    /* IMG 1
     *
     * 0 0 0 0 0 0 0 0
     * 0 1 1 1 0 0 0 0
     * 0 1 1 1 0 0 0 0
     * 0 1 1 1 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     *
     */
    Image img = Image(8, 8, {
            0,0,0,0,0,0,0,0,
            0,255,255,255,0,0,0,0,
            0,255,255,255,0,0,0,0,
            0,255,255,255,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0
    });

    std::vector<unsigned char> kernel = std::vector<unsigned char> {
            1, 1, 1,
            1, 1, 1,
            1, 1, 1
    };

    img.writePPM("before.ppm");
    auto dilated = Morphology::dilate(img, kernel, 3, 3);
    dilated.writePPM("after_dilate.ppm");
    auto eroded = Morphology::erode(img, kernel, 3, 3);
    eroded.writePPM("after_erode.ppm");
    auto dilatedEroded = Morphology::erode(dilated, kernel, 3, 3);
    dilatedEroded.writePPM("after_dilate_erode.ppm");
}

void crossKernel() {
    Chronometer chrono = Chronometer();
    /* IMG 1
     *
     * 0 0 0 0 0 0 0 0
     * 0 1 1 1 0 0 0 0
     * 0 1 1 1 0 0 0 0
     * 0 1 1 1 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     * 0 0 0 0 0 0 0 0
     *
     */
    Image img = Image(8, 8, {
            0,0,0,0,0,0,0,0,
            0,255,255,255,0,0,0,0,
            0,255,255,255,0,0,0,0,
            0,255,255,255,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0
    });

    std::vector<unsigned char> kernel = std::vector<unsigned char> {
            0, 1, 0,
            1, 1, 1,
            0, 1, 0
    };

    img.writePPM("before.ppm");
    auto dilated = Morphology::dilate(img, kernel, 3, 3);
    dilated.writePPM("after_dilate.ppm");
    auto eroded = Morphology::erode(img, kernel, 3, 3);
    eroded.writePPM("after_erode.ppm");
    auto dilatedEroded = Morphology::erode(dilated, kernel, 3, 3);
    dilatedEroded.writePPM("after_dilate_erode.ppm");
}

void complexImage(Image &img, unsigned iterations) {
    Chronometer chrono = Chronometer();

    std::vector<unsigned char> kernel = std::vector<unsigned char> {
            0, 1, 0,
            1, 1, 1,
            0, 1, 0
    };

    img.writePPM("before.ppm");
    auto dilated = Morphology::dilate(img, kernel, 3, 3, iterations);
    dilated.writePPM("after_dilate.ppm");
    auto eroded = Morphology::erode(img, kernel, 3, 3, iterations);
    eroded.writePPM("after_erode.ppm");
    auto dilatedEroded = Morphology::erode(dilated, kernel, 3, 3, iterations);
    dilatedEroded.writePPM("after_dilate_erode.ppm");
}


int main() {

//    crossKernel();
    Image loaded = Image::fromPPM("../Data/compo.ppm");
    complexImage(loaded, 10);
    return 0;
}