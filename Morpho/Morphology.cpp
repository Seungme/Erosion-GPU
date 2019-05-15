//
// Created by revetoon on 5/13/19.
//

#include "Morphology.hh"

unsigned char unitErode(const std::vector<unsigned char> &vals) {
    for (const auto &v : vals) {
        if (v == 0)
            return 0;
    }
    return 255;
}

unsigned char unitDilate(const std::vector<unsigned char> &vals) {
    for (const auto &v : vals) {
        if (v != 0)
            return 255;
    }
    return 0;
}

Image Morphology::erode(Image &img, const std::vector<unsigned char> &kernel, int w, int h, unsigned iteration) {
    Image r = img;
    for (int i = 0; i < iteration; ++i) {
        r = convolute(r, kernel, w, h, unitErode, 255);

    }
    return r;
}

Image Morphology::dilate(Image &img, const std::vector<unsigned char> &kernel, int w, int h, unsigned iteration) {
    Image r = img;
    for (int i = 0; i < iteration; ++i) {
        r = convolute(r, kernel, w, h, unitDilate, 0);
    }
    return r;
}

Image Morphology::convolute(Image &img, const std::vector<unsigned char> &kernel, int w, int h,
                           morphTransfo morphFunction, int oobVal) {
    Image newImg = Image(img.getWidth(), img.getHeight());
    int centery = h / 2;
    int centerx = w / 2;
    std::vector<unsigned char> vals = std::vector<unsigned char>();
    for (int y = 0; y < img.getHeight(); ++y) {
        for (int x = 0; x < img.getWidth(); ++x) {
            vals.clear();
            for (int n = 0; n < h; ++n) {
                for (int m = 0; m < h; ++m) {
                    // skip if point in kernel in a zero
                    if (kernel[n * w + m] == 0)
                        continue;
                    if ((x + m - centerx) < 0 ||
                        (x + m - centerx) >= img.getWidth() ||
                        (y + n - centery) < 0 ||
                        (y + n - centery) >= img.getHeight()) {
                        // outside the image pixels are interpreted are zeros
                        vals.push_back(oobVal);
                    } else {
                        vals.push_back(img.getPixel((x + m - centerx), (y + n - centery)));
                    }
                }
            }
            unsigned char r = morphFunction(vals);
            newImg.setPixel(x, y, r);
        }
    }
    return newImg;
}
