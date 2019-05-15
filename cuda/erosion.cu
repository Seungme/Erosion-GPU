#include <cuda_runtime.h>
//#include <helper_cuda.h>
#include <cstdint>
#include <iostream>
#include <stdio.h>

__global__ void helloOnGPU()
{
    printf("Hello World on GPU!\n");
}

__global__ void erosion(uint8_t *orig, uint8_t *morphed, unsigned width) {
    int indexX = blockIdx.x * blockDim.x + threadIdx.x;
    // int indexY = blockIdx.y * blockDim.y + threadIdx.y;
    //printf("%d, %c ", indexX, orig[indexX]);
    //printf("%d ", indexX);
    // printf("%c ", orig[indexX]);
    // morphed[indexY * width + indexX] = orig[indexY * width + indexX];

    morphed[indexX] = orig[indexX];
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

    // helloOnGPU<<<1, 10>>>();

    uint8_t *ma = new uint8_t[9] { 'E', 'A', 'j', '1', 'h', '0', 'q', 'd', 'w' };
    uint8_t *mo = new uint8_t[9] { 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x' };

    uint8_t *mat;
    uint8_t *morphed;
    cudaMalloc(&mat, 9 * sizeof (uint8_t));
    cudaMalloc(&morphed, 9 * sizeof (uint8_t));

    cudaMemcpy(mat, ma, sizeof(uint8_t) * 9, cudaMemcpyHostToDevice);
    cudaMemcpy(morphed, mo, sizeof(uint8_t) * 9, cudaMemcpyHostToDevice);


    printMat(ma, 9);

    int nthreads = 9;
    const int n = 128 * 1024;
    int blockSize = 512;
    int nbBlocks = n / nthreads;
    // dim3 grids(3, 3);
    // dim3 threads
    // std::cout << "nbBlocks: " << nbBlocks << "  blockSize: " << blockSize << std::endl;
    
    erosion<<<1, 9>>>(mat, morphed, 3);

    cudaMemcpy(mo, morphed, sizeof (uint8_t) * 9, cudaMemcpyDeviceToHost);

    printMat(mo, 9);

    return 0;
}

