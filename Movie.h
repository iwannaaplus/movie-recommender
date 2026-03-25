#pragma once
#include <string>
using namespace std;

class Movie {
private:
    int id;
    string title;
    string genre;
    int year;
    double totalRating;
    int ratingCount;

public:
    Movie();
    Movie(int id, string title, string genre, int year);

    int getId() const;
    string getTitle() const;
    string getGenre() const;
    int getYear() const;
    double getAverageRating() const;

    void addRating(double rating);
    void display() const;
};