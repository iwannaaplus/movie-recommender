#pragma once
#include <vector>
#include <set>
#include <map>
#include "Movie.h"
#include "MovieManager.h"
#include "RatingManager.h"

class Recommender {
private:
    MovieManager& movieMgr;
    RatingManager& ratingMgr;

    std::vector<Rating> getTargetUserRatings(int targetUserId) const;
    std::set<int> extractMovieIds(const std::vector<Rating>& ratings) const;
    std::vector<std::pair<int, int>> calculateAllSimilarities(int targetUserId, const std::vector<Rating>& myRatings) const;
    std::map<int, double> computeMovieScores(const std::vector<std::pair<int, int>>& similarities, const std::set<int>& myMovieIds) const;

public:
    Recommender(MovieManager& mMgr, RatingManager& rMgr);
    std::vector<Movie> recommend(int targetUserId);
};