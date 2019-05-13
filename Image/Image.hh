//
// Created by revetoon on 4/5/19.
//

#ifndef EROSION_GPU_PPM_HH
#define EROSION_GPU_PPM_HH

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Image {
public:
    Image(int width, int height);
    Image(int width, int height, const std::vector<unsigned char> &pxls);

    void setPixel(int x, int y, unsigned char val);

    unsigned char getPixel(int x, int y) const;

    void writePPM(const std::string &filename) const;

    int getWidth() const;

    int getHeight() const;

    static Image fromPPM(const std::string &filename);

private:


private:
    std::vector<unsigned char> pixels;
    int width;
    int height;
};

#endif //EROSION_GPU_PPM_HH
