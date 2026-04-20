#include "Movie.h"
#include <iostream>

Movie::Movie()
    : id(0), title(""), genre(""), year(0), totalRating(0.0), ratingCount(0) {
}

Movie::Movie(int id, std::string title, std::string genre, int year)
    : id(id), title(title), genre(genre), year(year), totalRating(0.0), ratingCount(0) {
}

int Movie::getId() const {
    return id;
}

std::string Movie::getTitle() const {
    return title;
}

std::string Movie::getGenre() const {
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
    std::cout << "ID: " << id << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Average Rating: " << getAverageRating() << std::endl;
}
bool Movie::operator==(const Movie& other) const {
    return this->title == other.title
        && this->year == other.year;
}
bool Movie::operator<(const Movie& other) const {
    return this->getAverageRating() < other.getAverageRating();
}
std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << m.getId() << ". " << m.getTitle()
       << " (" << m.getYear() << ") "
       << "평점: " << m.getAverageRating();
    return os;
}