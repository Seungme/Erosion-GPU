//
// Created by revetoon on 4/5/19.
//

#ifndef EROSION_GPU_PPM_HH
#define EROSION_GPU_PPM_HH

#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <iostream>
#include <fstream>

class Image {
public:
    enum class ImportType {
        BINARY,
        GRAY
    };

public:
    Image(int width, int height);
    Image(int width, int height, uint8_t *pxls);

    void setPixel(int x, int y, unsigned char val);

    uint8_t getPixel(int x, int y) const;

    uint8_t *pixelArray();

    void writePPM(const std::string &filename) const;

    int getWidth() const;

    int getHeight() const;

    static Image fromPPM(const std::string &filename, ImportType type = ImportType::GRAY);

private:
    uint8_t *pixels;
    int width;
    int height;
};

#endif //EROSION_GPU_PPM_HH
