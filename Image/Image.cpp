//
// Created by revetoon on 4/5/19.
//

#include "Image.hh"
#include <exception>

Image::Image(int width, int height)
        :pixels(new uint8_t[width * height]()),
         width(width),
         height(height)
{
}

Image::Image(int width, int height, uint8_t *pxls)
        :pixels(pxls),
         width(width),
         height(height)
{
}

void Image::writePPM(const std::string &filename) const {
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

void Image::setPixel(int x, int y, unsigned char val) {
    pixels[y * width + x] = val;
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

uint8_t Image::getPixel(int x, int y) const {
    return pixels[y * width + x];
}

Image Image::fromPPM(const std::string &filename, ImportType type) {
    std::ifstream is(filename);
    std::string str;
    is >> str; // P6
    if (str != "P6")
        throw std::domain_error("Wrong header.");
    int width, height, colors;
    is >> width >> height >> colors;
    if (width <= 0 || height <= 0)
        throw std::domain_error("Wrong dimensions.");
    Image img = Image(width, height);

    char r;
    char g;
    char b;
    long i = 0;
    while (!is.eof()) {
        is.get(r); // r
        is.get(g); // g
        is.get(b); // b
        if (type == ImportType::GRAY) { // GRAY
            img.pixels[i++] = (static_cast<unsigned char>(r) * 0.2126 +
                               static_cast<unsigned char>(g) * 0.7152 +
                    static_cast<unsigned char>(b) * 0.0722); // > 127 ? 255 : 0;
        } else {                        // BINARY
            img.pixels[i++] = (static_cast<unsigned int>(r) +
                               static_cast<unsigned int>(g) +
                               static_cast<unsigned int>(b)) / 3.0 > 127 ? 255 : 0;
        }
    }
    if (i - 1 != width * height)
        throw std::domain_error("Wrong number of pixels (" + std::to_string(i) + " != " + std::to_string(width * height) +  ").");
    return img;
}

uint8_t *Image::pixelArray() {

}

