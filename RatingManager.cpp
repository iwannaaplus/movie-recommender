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

void RatingManager::addRatingFromInput(MovieManager& manager) {
    int userId, movieId;
    double score;

    std::cout << "사용자 ID: ";
    std::cin >> userId;
    std::cout << "영화 ID: ";
    std::cin >> movieId;
    std::cout << "평점: ";
    std::cin >> score;

    Rating r(userId, movieId, score);
    ratings.push_back(r);

    Movie* m = manager.findById(movieId);
    if (m != nullptr) {
        m->addRating(score);
    }
}

void RatingManager::loadFromFile(const std::string& filename) {
}

void RatingManager::saveToFile(const std::string& filename) const {
}

int RatingManager::size() const {
    return ratings.size();
}