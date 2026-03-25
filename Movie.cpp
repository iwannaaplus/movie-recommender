#include "Movie.h"
#include <iostream>
using namespace std;

Movie::Movie()
    : id(0), title(""), genre(""), year(0), totalRating(0.0), ratingCount(0) {
}

Movie::Movie(int id, string title, string genre, int year)
    : id(id), title(title), genre(genre), year(year), totalRating(0.0), ratingCount(0) {
}

int Movie::getId() const {
    return id;
}

string Movie::getTitle() const {
    return title;
}

string Movie::getGenre() const {
    return genre;
}

int Movie::getYear() const {
    return year;
}

double Movie::getAverageRating() const {
    if (ratingCount == 0) {
        return 0.0;
    }
    return totalRating / ratingCount;
}

void Movie::addRating(double rating) {
    if (rating >= 0.0 && rating <= 5.0) {
        totalRating += rating;
        ratingCount++;
    }
}

void Movie::display() const {
    cout << "ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Genre: " << genre << endl;
    cout << "Year: " << year << endl;
    cout << "Average Rating: " << getAverageRating() << endl;
}