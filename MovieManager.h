#pragma once
#include <vector>
#include <string>
#include "Movie.h"

class MovieManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie& m);
    void printAll() const;
    Movie* findByTitle(const std::string& title);
    Movie* findById(int id);
    void sortByRating();

    void addMovieFromInput();
    void searchMovie();
};