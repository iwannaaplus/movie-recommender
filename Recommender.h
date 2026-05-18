#pragma once
#include <vector>
#include "Movie.h"
#include "MovieManager.h"
#include "RatingManager.h"

class Recommender {
private:
    MovieManager& movieMgr;
    RatingManager& ratingMgr;

public:
    Recommender(MovieManager& mMgr, RatingManager& rMgr);
    std::vector<Movie> recommend(int targetUserId);
};