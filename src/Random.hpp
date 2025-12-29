#pragma once
#include <random>

inline std::mt19937 rng(std::random_device{}());

inline int randomInt(const int min, const int max) {
    std::uniform_int_distribution dist(min, max);
    return dist(rng);
}

inline float randomFloat(const float min, const float max) {
    std::uniform_real_distribution dist(min, max);
    return dist(rng);
}