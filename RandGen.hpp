#pragma once
#include <random>

class RandGen {
private:
    static std::mt19937 mt;
public:
    static int get_int(int min, int max);
};
