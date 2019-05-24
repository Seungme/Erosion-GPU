#include <cuda_runtime.h>
//#include <helper_cuda.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include "../Image/Image.hh"
#include "../Chronometer.hh"
#include "../CPU/Morphology.hh"

__global__ void copy(uint8_t *orig, uint8_t *morphed, unsigned width) {
    int indexX = blockIdx.x * blockDim.x + threadIdx.x;
    int indexY = blockIdx.y * blockDim.y + threadIdx.y;
    //printf("%d, %c ", indexX, orig[indexX]);
    printf("[x: %d, y: %d] ", indexX, indexY);
    // printf("%c ", orig[indexX]);
    // morphed[indexY * width + indexX] = orig[indexY * width + indexX];

    morphed[indexY * width + indexX] = orig[indexY * width + indexX];
}

void printMat(uint8_t *mat, unsigned w, unsigned h) {

    std::cout << "[ " << std::endl;
for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            std::cout << static_cast<unsigned>(mat[i * w + j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
}




__global__ void erosion(uint8_t *orig, unsigned origWidth, unsigned origHeight,
                         uint8_t *morphed, unsigned width,
                         uint8_t *ker, unsigned side) {
    int kerMid = side / 2;
    int indexX = blockIdx.x * blockDim.x + threadIdx.x + kerMid;
    int indexY = blockIdx.y * blockDim.y + threadIdx.y + kerMid;

    if (indexX < kerMid || indexX >= origWidth - kerMid
        || indexY < kerMid || indexY >= origHeight - kerMid)
        return;

    morphed[(indexY - kerMid) * width + (indexX - kerMid)] = 255;
    
    for (int y = 0; y < side; ++y) {
        for (int x = 0; x < side; ++x) {
            if (ker[y * side + x]) {

                morphed[(indexX - kerMid) + (indexY - kerMid) * width] = min(
                        morphed[(indexY - kerMid) * width + (indexX - kerMid)],
                        orig[(indexX + x - kerMid) + (indexY + y - kerMid) * origWidth]
                        );
            }
        }

    }
}

__global__ void dilation(uint8_t *orig, unsigned origWidth, unsigned origHeight,
                         uint8_t *morphed, unsigned width,
                         uint8_t *ker, unsigned side) {
    int kerMid = side / 2;
    int indexX = blockIdx.x * blockDim.x + threadIdx.x + kerMid;
    int indexY = blockIdx.y * blockDim.y + threadIdx.y + kerMid;

    if (indexX < kerMid || indexX >= origWidth - kerMid
        || indexY < kerMid || indexY >= origHeight - kerMid)
        return;

    morphed[(indexY - kerMid) * width + (indexX - kerMid)] = 0;
    
    for (int y = 0; y < side; ++y) {
        for (int x = 0; x < side; ++x) {
            if (ker[y * side + x]) {

                morphed[(indexX - kerMid) + (indexY - kerMid) * width] = max(
                        morphed[(indexY - kerMid) * width + (indexX - kerMid)],
                        orig[(indexX + x - kerMid) + (indexY + y - kerMid) * origWidth]
                        );
            }
        }

    }
}


int ceilDivision(int a, int b) {
    if (a % b == 0)
        return a / b;
    return a / b + 1;
}


Image benchDilate(Image &img, uint8_t *kernel, int iterations) {
    Chronometer chrono = Chronometer("[GPU] Dilate");

    Image padded = Image::addPadding(img, ker.size() / 2, 0);

    uint8_t *result = new uint8_t[img.getHeight() * img.getWidth()];

    unsigned int max = 512;
    unsigned int gridw = ceilDivision(padded.getWidth(), max);
    unsigned int gridh = ceilDivision(padded.getHeight(), max);

    dim3 grids(gridw, gridh);
    dim3 threads(max, max);


//    std::cout << "padW: " << paddedWidth << " padH: " << paddedHeight << std::endl;
//    std::cout << "gridw: " << gridw << " gridh: " << gridh  << " threads: " << max << std::endl;

    uint8_t *orig;
    uint8_t *morphed;
    uint8_t *ker;

    cudaMalloc(&orig, sizeof (uint8_t) * (gridw * max) * (gridh * max));
    cudaMalloc(&morphed, sizeof (uint8_t) * imgWidth * imgHeight);
    cudaMalloc(&ker, sizeof (uint8_t) * kerSide * kerSide);

    cudaMemcpy(orig, padded, sizeof (uint8_t) * (gridw * max) * (gridh * max), cudaMemcpyHostToDevice);
    cudaMemcpy(ker, kernel, sizeof (uint8_t) * kerSide * kerSide, cudaMemcpyHostToDevice);

    printMat(padded, 15, 15);
    //printMat(result, 13, 13);

    erosion<<<grids, threads>>>(orig, padded.getWidth(), padded.getHeight(), morphed, imgWidth, ker, kerSide);
    //printf("orig: %d\n",  orig[indexY * width + indexX] );

    cudaDeviceSynchronize();

    cudaMemcpy(result, morphed, sizeof (uint8_t) * imgWidth * imgHeight, cudaMemcpyDeviceToHost);

    std::cout << static_cast<int>(result[7]) << std::endl;

    cudaDeviceSynchronize();
//    printMat(result, 13, 13);

    cudaFree(morphed);
    cudaFree(orig);
    cudaFree(ker);

    return Image(img.getWidth(), img.getHeight(), result);
}

int main(int argc, char **argv)
{

    Image img = Image::fromPPM("../Data/RealSnake.ppm", Image::ImportType::BINARY);
    unsigned char *kernel = Morphology::kerSquareArray(3);
    benchDilate(img, kernel, 1);

    return 0;
}

