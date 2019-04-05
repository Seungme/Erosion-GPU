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

class PPM {
public:
    PPM(int width, int height);

    void writePPM(const std::string &filename);
private:


private:
    std::vector<unsigned char> pixels;
    int width;
    int height;
};

#endif //EROSION_GPU_PPM_HH
