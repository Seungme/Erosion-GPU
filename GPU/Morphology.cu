#include <cuda_runtime.h>
//#include <helper_cuda.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>

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


//int main(int argc, char **argv)
//{
//
//    // img
//    uint8_t img[9] = { 1, 1, 1,
//                       1, 1, 1,
//                       1, 1, 1 };
//    unsigned int imgWidth = 13;
//    unsigned int imgHeight = 13;
//    // kernel
//    uint8_t kernel[9] = { 1, 1, 1,
//                          1, 1, 1,
//                          1, 1, 1 };
//    unsigned int kerSide = 3;
//    // paddedImg
//    /*
//    uint8_t paddedImg[25] =   { 0, 0, 0, 0, 0,
//                                0, 0, 0, 0, 0,
//                                0, 0, 1, 0, 0,
//                                0, 0, 0, 0, 0,
//                                0, 0, 0, 0, 0 };
//*/
//    uint8_t paddedImg[225] = {
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
//    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//    };
///*
//    uint8_t *result = new uint8_t[25] { 128, 128, 128, 128, 128,
//                                        128, 128, 128, 128, 128,
//                                        128, 128, 128, 128, 128,
//                                        128, 128, 128, 128, 128,
//                                        128, 128, 128, 128, 128 };
//*/
//    uint8_t *result = new uint8_t[196]();
//
//    unsigned int paddedWidth  = imgWidth  + (kerSide  / 2) * 2;
//    unsigned int paddedHeight = imgHeight + (kerSide / 2) * 2;
//
//    unsigned int max = 8;
//    unsigned int gridw = ceilDivision(paddedWidth, max);
//    unsigned int gridh = ceilDivision(paddedHeight, max);
//
//    dim3 grids(gridw, gridh);
//    dim3 threads(max, max);
//
//
//    std::cout << "padW: " << paddedWidth << " padH: " << paddedHeight << std::endl;
//    std::cout << "gridw: " << gridw << " gridh: " << gridh  << " threads: " << max << std::endl;
//    // TODO multithread cudaMalloc
//
//    uint8_t *orig;
//    uint8_t *eroded;
//    uint8_t *ker;
//
//    cudaMalloc(&orig, sizeof (uint8_t) * (gridw * max) * (gridh * max));
//    cudaMalloc(&eroded, sizeof (uint8_t) * imgWidth * imgHeight);
//    cudaMalloc(&ker, sizeof (uint8_t) * kerSide * kerSide);
//
//    cudaMemcpy(orig, paddedImg, sizeof (uint8_t) * (gridw * max) * (gridh * max), cudaMemcpyHostToDevice);
//    cudaMemcpy(ker, kernel, sizeof (uint8_t) * kerSide * kerSide, cudaMemcpyHostToDevice);
//
//    printMat(paddedImg, 15, 15);
//    //printMat(result, 13, 13);
//
//    erosion<<<grids, threads>>>(orig, paddedWidth, paddedHeight, eroded, imgWidth, ker, kerSide);
//    //printf("orig: %d\n",  orig[indexY * width + indexX] );
//
//    cudaDeviceSynchronize();
//
//    cudaMemcpy(result, eroded, sizeof (uint8_t) * imgWidth * imgHeight, cudaMemcpyDeviceToHost);
//
//    std::cout << static_cast<int>(result[7]) << std::endl;
//
//    cudaDeviceSynchronize();
//    printMat(result, 13, 13);
//
//
//    cudaFree(eroded);
//    cudaFree(orig);
//    cudaFree(ker);
//
//    return 0;
//
/*



    // data on HOST memory
    uint8_t *ma = new uint8_t[9] { 'E', 'A', 'j', '1', 'h', '0', 'q', 'd', 'w' };
    uint8_t *mo = new uint8_t[9] { 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x' };

    // GPU memory allocation
    uint8_t *mat;
    uint8_t *morphed;
    cudaMalloc(&mat, 9 * sizeof (uint8_t));
    cudaMalloc(&morphed, 9 * sizeof (uint8_t));

    // copy HOST memory to GPU memory
    cudaMemcpy(mat, ma, sizeof(uint8_t) * 9, cudaMemcpyHostToDevice);
    cudaMemcpy(morphed, mo, sizeof(uint8_t) * 9, cudaMemcpyHostToDevice);


    printMat(ma, 9);

    int nthreads = 9;
    const int n = 128 * 1024;
    int blockSize = 512;
    int nbBlocks = n / nthreads;
    dim3 grids(3, 3);


    // compute on GPU
    erosion<<<grids, threads>>>(mat, morphed, 3);

    // copy back GPU memory to HOST memory
    cudaMemcpy(mo, morphed, sizeof (uint8_t) * 9, cudaMemcpyDeviceToHost);

    printMat(mo, 9);

    return 0;

*/

}

