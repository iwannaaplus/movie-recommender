#include "Recommender.h"
#include "SimilarityCalculator.h"
#include "MovieConstants.h"
#include <algorithm>

Recommender::Recommender(MovieManager& mMgr, RatingManager& rMgr) 
    : movieMgr(mMgr), ratingMgr(rMgr) {}

std::vector<Movie> Recommender::recommend(int targetUserId) {
    std::vector<Movie> recommendations;

    auto myRatings = getTargetUserRatings(targetUserId);
    if (myRatings.empty()) return recommendations;

    auto myMovieIds = extractMovieIds(myRatings);
    auto similarities = calculateAllSimilarities(targetUserId, myRatings);
    
    if (similarities.empty()) return recommendations;

    auto movieScores = computeMovieScores(similarities, myMovieIds);

    std::vector<std::pair<int, double>> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (const auto& pair : sortedMovies) {
        try {
            Movie& m = movieMgr.findById(pair.first);
            recommendations.push_back(m);
        } catch (const std::out_of_range&) {
            continue; 
        }
    }

    return recommendations;
}

std::vector<Rating> Recommender::getTargetUserRatings(int targetUserId) const {
    std::vector<Rating> myRatings;
    for (const auto& r : ratingMgr.getRatings()) {
        if (r.getUserId() == targetUserId) myRatings.push_back(r);
    }
    return myRatings;
}

std::set<int> Recommender::extractMovieIds(const std::vector<Rating>& ratings) const {
    std::set<int> movieIds;
    for (const auto& r : ratings) movieIds.insert(r.getMovieId());
    return movieIds;
}

std::vector<std::pair<int, int>> Recommender::calculateAllSimilarities(int targetUserId, const std::vector<Rating>& myRatings) const {
    std::vector<std::pair<int, int>> similarities;
    std::vector<int> allUsers;
    
    for (const auto& r : ratingMgr.getRatings()) {
        int uid = r.getUserId();
        if (uid != targetUserId && std::find(allUsers.begin(), allUsers.end(), uid) == allUsers.end()) {
            allUsers.push_back(uid);
        }
    }

    for (int otherId : allUsers) {
        std::vector<Rating> otherRatings = getTargetUserRatings(otherId);
        int sim = SimilarityCalculator::Similaritycalculate(myRatings, otherRatings);
        if (sim != MovieConstants::INVALID_SIMILARITY) {
            similarities.push_back({otherId, sim});
        }
    }

    std::sort(similarities.begin(), similarities.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    return similarities;
}

std::map<int, double> Recommender::computeMovieScores(const std::vector<std::pair<int, int>>& similarities, const std::set<int>& myMovieIds) const {
    std::map<int, double> movieScores;
    std::size_t neighborsCount = std::min(MovieConstants::MAX_NEIGHBORS, similarities.size());

    for (std::size_t i = 0; i < neighborsCount; ++i) {
        int neighborId = similarities[i].first;
        for (const auto& r : ratingMgr.getRatings()) {
            if (r.getUserId() == neighborId && myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                movieScores[r.getMovieId()] += r.getScore();
            }
        }
    }
    return movieScores;
}