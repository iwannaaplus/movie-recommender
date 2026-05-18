#include "Movie.h"

Movie::Movie()
    : id(0), title(""), genre(""), year(0), totalRating(0.0), ratingCount(0) {}

Movie::Movie(int id, std::string title, std::string genre, int year)
    : id(id), title(title), genre(genre), year(year), totalRating(0.0), ratingCount(0) {}

Movie::Movie(int id, std::string title, std::string genre, int year, double totalRating, int ratingCount)
    : id(id), title(title), genre(genre), year(year), totalRating(totalRating), ratingCount(ratingCount) {}

int Movie::getId() const { return id; }
std::string Movie::getTitle() const { return title; }
std::string Movie::getGenre() const { return genre; }
int Movie::getYear() const { return year; }
double Movie::totalRatingValue() const { return totalRating; }
int Movie::ratingCountValue() const { return ratingCount; }

double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;
    return totalRating / ratingCount;
}

void Movie::addRating(double rating) {
    if (rating >= 0.0 && rating <= 5.0) {
        totalRating += rating;
        ratingCount++;
    }
}

bool Movie::operator==(const Movie& other) const {
    return title == other.title && year == other.year;
}

bool Movie::operator<(const Movie& other) const {
    return getAverageRating() < other.getAverageRating();
}

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << m.id << ". " << m.title
       << " (" << m.year << ") "
       << "평점: " << m.getAverageRating();
    return os;
}