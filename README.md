# Erosion and dilation CPU/GPU

## Introduction

This code lets you apply the most common morphological operators to
an image. 
The project implements the erosion and dilation operators.  
The idea was to compare CPU vs GPU performances on morphological 
operators.

## Installation & Run

#### Requirements

This project uses Nvidia's **Cuda**, you will need a Nvidia GPU and `nvcc`
installed.
You can still run the cpu version even if you don't have `nvcc` !


#### Build

You can build multiple targets:  
###### Cpu version
```
make cpu
```
Will output `./CPU_EXEC`

###### Cpu vectorized version
```
make vect
```
Will output `./CPU_VECT_EXEC`

###### Gpu version
```
make gpu
```
Will output `./GPU_EXEC`

###### Utilities
```
make clean          # clean binaries
make clean-imgs     # clean images
```

#### Run

```
./CPU_EXEC INPUT_IMAGE [KERNEL_SIZE] [KERNEL_SHAPE]
./CPU_VECT_EXEC INPUT_IMAGE [KERNEL_SIZE] [KERNEL_SHAPE]
./GPU_EXEC INPUT_IMAGE [KERNEL_SIZE] [KERNEL_SHAPE]

# Example ./CPU_EXEC ./Data/RealSnake.ppm 5 'circle'
```

## Benchmarks

Benchmarks are built using shell scripts lcoated in `./benchmark/`, the
output is a `csv` file containing the values that you can plot later
on.  
You **must** run `./Data/bench/genImgs.sh` before running the benchmarks.
```
./Data/bench/genImgs.sh INPUT_IMAGE

# Example: ./genImgs.sh ../RealSnake.ppm
```
Benchmark by image size: 
```
./benchImgsize.sh EXECUTABLE OUTPUT_CSV_FILE

# Example
# ./benchImgsize.sh ../CPU_EXEC 'CpuImgBench.csv'
```
Benchmark by kernel size: 
```
./benchKersize.sh EXECUTABLE OUTPUT_CSV_FILE

# Example
# ./benchKersize.sh ../CPU_EXEC 'CpuKerBench.csv'
```
Feel free to modify the scripts !
