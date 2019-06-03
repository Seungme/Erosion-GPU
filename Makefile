CC = g++
CPP_FILES = Examples.cpp Chronometer.cpp CPU/Morphology.cpp Image/Image.cpp
GPU_FILE = GPU/MorphologyGPU.cu
OBJ_FILES = $(CPP_FILES:.cpp=.o)

CXX_FLAGS += -Wall -Wextra -std=c++11
LDXX_FLAGS =


cpu: $(OBJ_FILES)
	$(CC) main.cpp -o CPU_EXEC $(OBJ_FILES) $(CXX_FLAGS) $(LDXX_FLAGS)
	rm *.o

gpu: $(OBJ_FILES)
	nvcc -o GPU_EXEC $(OBJ_FILES) $(GPU_FILE)
	rm *.o

.PHONY: CPU_EXEC GPU_EXEC

clean:
	rm CPU GPU
