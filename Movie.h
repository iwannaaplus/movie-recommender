#pragma once
#include <string>
#include <iostream>

class Movie {
private:
    int id;
    std::string title;
    std::string genre;
    int year;
    double totalRating;
    int ratingCount;

public:
    Movie();
    Movie(int id, std::string title, std::string genre, int year);
    Movie(int id, std::string title, std::string genre, int year, double totalRating, int ratingCount);

    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getYear() const;
    double totalRatingValue() const;
    int ratingCountValue() const;
    double getAverageRating() const;

    void addRating(double rating);

    bool operator==(const Movie& other) const;
    bool operator<(const Movie& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};