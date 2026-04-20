#pragma once
#include <vector>
#include "Movie.h"

class MovieManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie& m);
    void printAll() const;
    Movie* findByTitle(const std::string& title);
};