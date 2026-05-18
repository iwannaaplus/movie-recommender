#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void RatingManager::addRating(const Rating& r) {
    ratings.push_back(r);
}

void RatingManager::printAll() const {
    for (const Rating& r : ratings) {
        r.display();
        std::cout << std::endl;
    }
}

void RatingManager::addRatingFromInput() {
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
}

void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int userId = std::stoi(token);

        std::getline(ss, token, ',');
        int movieId = std::stoi(token);

        std::getline(ss, token, ',');
        double score = std::stod(token);

        ratings.push_back(Rating(userId, movieId, score));
    }
    file.close();
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "userId,movieId,score" << std::endl;
    for (const auto& r : ratings) {
        file << r.getUserId() << ","
             << r.getMovieId() << ","
             << r.getScore() << std::endl;
    }
    file.close();
}

int RatingManager::size() const {
    return ratings.size();
}