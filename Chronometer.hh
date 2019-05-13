//
// Created by revetoon on 5/13/19.
//

#ifndef EROSION_GPU_CHRONOMETRE_HH
#define EROSION_GPU_CHRONOMETRE_HH


#include <chrono>
#include <iostream>
#include <iomanip>

class Chronometer {
    typedef std::chrono::time_point<std::chrono::steady_clock> timePt;

public:
    Chronometer();
    Chronometer(const std::string &name);

    ~Chronometer();

private:
    std::string name = "";
    timePt start = std::chrono::steady_clock().now();
};


#endif //EROSION_GPU_CHRONOMETRE_HH

