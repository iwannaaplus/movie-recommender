#include "Rating.h"
#include <iostream>
using namespace std;

Rating::Rating(int userId, int movieId, double score)
    : userId(userId), movieId(movieId) {
    if (score >= 0.0 && score <= 5.0) {
        this->score = score;
    } else {
        this->score = 0.0;
    }
}

int Rating::getUserId() const {
    return userId;
}

int Rating::getMovieId() const {
    return movieId;
}

double Rating::getScore() const {
    return score;
}

void Rating::display() const {
    cout << "User ID: " << userId << endl;
    cout << "Movie ID: " << movieId << endl;
    cout << "Score: " << score << endl;
}