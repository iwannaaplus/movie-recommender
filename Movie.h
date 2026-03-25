#pragma once
#include <string>

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

    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getYear() const;
    double getAverageRating() const;

    void addRating(double rating);
    void display() const;
};