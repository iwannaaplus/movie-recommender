#include "MovieManager.h"
#include <iostream>

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