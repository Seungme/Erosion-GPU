//
// Created by revetoon on 5/13/19.
//

#include "Chronometer.hh"

Chronometer::Chronometer() {
}

Chronometer::Chronometer(const std::string &name)
        :name(name)
{}

Chronometer::~Chronometer() {
    timePt end = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = end - start;
//    if (!name.empty())
//        std::cout << name << " : ";
//    std::cout << "Execution time: " << std::setprecision(8) << std::to_string(diff.count()) << " secs." << std::endl;
    std::cout << std::setprecision(8) << std::to_string(diff.count()) << std::endl;
}
