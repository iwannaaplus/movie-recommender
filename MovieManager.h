#pragma once
#include <vector>
#include <string>
#include <map>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie& m);
    void printAll() const;
    
    Movie& findByTitle(const std::string& title);
    Movie& findById(int id);
    
    void sortByRating();

    void addMovieFromInput();
    void searchMovie();
    void updateMovieRating(int movieId, double score);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;

    double getAverageRating() const;
    std::map<std::string, double> getAverageRatingByGenre() const;
    std::vector<Movie> getTopN(int n) const;
    void exportStatisticsToCSV(const std::string& filename) const;
    void sortByTitle();
};