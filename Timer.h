#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::string label;

public:
    Timer(const std::string& l) : label(l) {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "[" << label << "] " << us.count() << " us" << std::endl;
    }
};