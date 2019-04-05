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

std::string PPM::toPPM() {
    std::ostringstream ss;
    ss << "P6\n";
    ss << width << " " << height << "\n";
    ss << "255\n";

    // TODO Write pixels
//    // Example

//    unsigned length = 0;
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) {
//            ss.put(static_cast<char>(pixels[length].getR()));
//            ss.put(static_cast<char>(pixels[length].getG()));
//            ss.put(static_cast<char>(pixels[length].getB()));
//            ++length;
//        }
//    }
    return ss.str();
}

void PPM::writePPM(const std::string &filename) {
    std::ofstream os(filename);
    os << toPPM();
    os.close();
}

