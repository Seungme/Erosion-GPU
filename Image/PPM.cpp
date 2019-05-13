//
// Created by revetoon on 4/5/19.
//

#include "PPM.hh"

PPM::PPM(int width, int height)
        :pixels(std::vector<unsigned char>(width * height)),
         width(width),
         height(height)
{
}


void PPM::writePPM(const std::string &filename) {
    std::ofstream os(filename);
    os << "P6\n";
    os << width << " " << height << "\n";
    os << "255\n";

    // TODO Write pixels
    // Example

    unsigned length = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            os.put(pixels[length]);
            os.put(pixels[length]);
            os.put(pixels[length]);
            ++length;
        }
    }
    os.close();
}

