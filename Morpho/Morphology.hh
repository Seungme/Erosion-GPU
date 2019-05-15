//
// Created by revetoon on 5/13/19.
//

#ifndef EROSION_GPU_MORPHOLOGY_HH
#define EROSION_GPU_MORPHOLOGY_HH


#include "../Image/Image.hh"

class Morphology {
    typedef unsigned char (*morphTransfo)(const std::vector<unsigned char> &);

public:
    static Image erode(Image &img, const std::vector<unsigned char> &kernel, int w, int h, unsigned iteration = 1);
    static Image dilate(Image &img, const std::vector<unsigned char> &kernel, int w, int h, unsigned iteration = 1);

private:
    static Image convolute(Image &img, const std::vector<unsigned char> &kernel, int w, int h, morphTransfo morphFunction, int oobVal);
};


#endif //EROSION_GPU_MORPHOLOGY_HH
