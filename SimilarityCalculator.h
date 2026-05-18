#pragma once
#include <vector>
#include "Rating.h"

class SimilarityCalculator {
public:
    static int Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB);
};