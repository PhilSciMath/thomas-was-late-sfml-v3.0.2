#include "RandGen.hpp"
#include <random>

std::mt19937 RandGen::mt{ std::random_device{}() };

int RandGen::get_int(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(mt);
}
