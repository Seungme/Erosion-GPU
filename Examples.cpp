//
// Created by revetoon on 5/24/19.
//

#include "Examples.hh"


namespace Examples {

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
        Image img = Image(8, 8, new uint8_t[8*8] {
                0,0,0,0,0,0,0,0,
                0,255,255,255,0,0,0,0,
                0,255,255,255,0,0,0,0,
                0,255,255,255,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0
        });

        auto kernel = Morphology::kerSquare(3);

        img.writePPM("before.ppm");
        auto dilated = Morphology::dilate(img, kernel);
        dilated.writePPM("after_dilate.ppm");
        auto eroded = Morphology::erode(img, kernel);
        eroded.writePPM("after_erode.ppm");
        auto dilatedEroded = Morphology::erode(dilated, kernel);
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
        Image img = Image(8, 8, new uint8_t[8*8] {
                0,0,0,0,0,0,0,0,
                0,255,255,255,0,0,0,0,
                0,255,255,255,0,0,0,0,
                0,255,255,255,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0
        });

        auto kernel = Morphology::kerSquare(3);

        img.writePPM("before.ppm");
        auto dilated = Morphology::dilate(img, kernel);
        dilated.writePPM("after_dilate.ppm");
        auto eroded = Morphology::erode(img, kernel);
        eroded.writePPM("after_erode.ppm");
        auto dilatedEroded = Morphology::erode(dilated, kernel);
        dilatedEroded.writePPM("after_dilate_erode.ppm");
    }

    void complexImage(Image &img, unsigned iterations) {
        Chronometer chrono = Chronometer();

//    std::vector<unsigned char> kernel = std::vector<unsigned char> {
//            0, 1, 0,
//            1, 1, 1,
//            0, 1, 0
//    };


//        std::vector<unsigned char> kernel = std::vector<unsigned char> {
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1,
//                1, 1, 1, 0, 0, 0, 1, 1, 1
//        };

        auto kernel = Morphology::kerCircle(5);


        img.writePPM("before.ppm");
        auto dilated = Morphology::dilate(img, kernel, iterations);
        dilated.writePPM("after_dilate.ppm");
        auto eroded = Morphology::erode(img, kernel, iterations);
        eroded.writePPM("after_erode.ppm");
        auto dilatedEroded = Morphology::erode(dilated, kernel, iterations);
        dilatedEroded.writePPM("after_dilate_erode.ppm");
    }

}