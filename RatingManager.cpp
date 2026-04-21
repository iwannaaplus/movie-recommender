#include "RatingManager.h"
#include <iostream>

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
}

void RatingManager::printAll() const {
    for (const Rating& r : ratings) {
        r.display();
        std::cout << std::endl;
    }
}