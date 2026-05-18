#include "MovieManager.h"
#include <iostream>
#include <algorithm>

void MovieManager::addMovie(const Movie& m) {
    movies.push_back(m);
}

void MovieManager::printAll() const {
    for (const Movie& m : movies) {
        std::cout << m << std::endl;
    }
}

Movie* MovieManager::findByTitle(const std::string& title) {
    for (Movie& m : movies) {
        if (m.getTitle() == title) {
            return &m;
        }
    }
    return nullptr;
}

Movie* MovieManager::findById(int id) {
    for (Movie& m : movies) {
        if (m.getId() == id) {
            return &m;
        }
    }
    return nullptr;
}

void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end());
}

void MovieManager::addMovieFromInput() {
    int id, year;
    std::string title, genre;

    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "제목: ";
    std::getline(std::cin, title);

    std::cout << "장르: ";
    std::getline(std::cin, genre);

    std::cout << "연도: ";
    std::cin >> year;

    addMovie(Movie(id, title, genre, year));
}

void MovieManager::searchMovie() {
    std::string title;
    std::cin.ignore();

    std::cout << "검색할 제목: ";
    std::getline(std::cin, title);

    Movie* m = findByTitle(title);

    if (m != nullptr) std::cout << *m << std::endl;
    else std::cout << "없음" << std::endl;
}

void MovieManager::updateMovieRating(int movieId, double score) {
    Movie* m = findById(movieId);
    if (m != nullptr) {
        m->addRating(score);
    }
}

void MovieManager::loadFromFile(const std::string& filename) {
}

void MovieManager::saveToFile(const std::string& filename) const {
}

int MovieManager::size() const {
    return movies.size();
}