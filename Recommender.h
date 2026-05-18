#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "MovieManager.h"
#include "RatingManager.h"

class Recommender {
public:
    static std::vector<Movie> recommend(int targetUserId, MovieManager& movieMgr, RatingManager& ratingMgr);
};