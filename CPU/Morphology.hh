//
// Created by revetoon on 5/13/19.
//

#ifndef EROSION_GPU_MORPHOLOGY_HH
#define EROSION_GPU_MORPHOLOGY_HH


#include "../Image/Image.hh"
#include <algorithm>

class Morphology {
    typedef unsigned char (*morphTransfo)(const std::vector<unsigned char> &);

public:
    static Image erode(Image &img, const std::vector<std::vector<unsigned char>> &kernel, unsigned iteration = 1);
    static Image dilate(Image &img, const std::vector<std::vector<unsigned char>> &kernel, unsigned iteration = 1);

    static std::vector<std::vector<unsigned char>> kerSquare(int side);
    static uint8_t *kerSquareArray(int side);
    static std::vector<std::vector<unsigned char>> kerSquare(int x, int y);
    static std::vector<std::vector<unsigned char>> kerCircle(int side);
    static uint8_t *kerCircleArray(int side);

private:
    static Image convolute(Image &img, const std::vector<std::vector<unsigned char>> &kernel, morphTransfo morphFunction, int oobVal);
};


#endif //EROSION_GPU_MORPHOLOGY_HH
