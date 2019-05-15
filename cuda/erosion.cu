#include <cuda_runtime.h>
//#include <helper_cuda.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>

__global__ void erosion(uint8_t *orig, uint8_t *morphed, unsigned width) {
    int indexX = blockIdx.x * blockDim.x + threadIdx.x;
    int indexY = blockIdx.y * blockDim.y + threadIdx.y;
    //printf("%d, %c ", indexX, orig[indexX]);
    printf("[x: %d, y: %d] ", indexX, indexY);
    // printf("%c ", orig[indexX]);
    // morphed[indexY * width + indexX] = orig[indexY * width + indexX];

    morphed[indexY * width + indexX] = orig[indexY * width + indexX];
}

void printMat(uint8_t *mat, unsigned size) {

    std::cout << "[ ";
    for (int i = 0; i < size; ++i) {
        std::cout << mat[i] << " ";
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char **argv)
{

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
    dim3 threads(3, 3);

    // compute on GPU
    erosion<<<grids, 1>>>(mat, morphed, 3);

    // copy back GPU memory to HOST memory
    cudaMemcpy(mo, morphed, sizeof (uint8_t) * 9, cudaMemcpyDeviceToHost);

    printMat(mo, 9);

    return 0;
}

