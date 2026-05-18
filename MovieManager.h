#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager {
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

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};