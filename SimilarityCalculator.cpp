#include "SimilarityCalculator.h"
#include <cstdlib>

int SimilarityCalculator::Similaritycalculate(const std::vector<Rating>& ratingsA, const std::vector<Rating>& ratingsB) {
    int commonCount = 0;
    int scoreDiffSum = 0;

    for (const Rating& r1 : ratingsA) {
        for (const Rating& r2 : ratingsB) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return -100;
    }

    return (commonCount * 10) - scoreDiffSum;
}