#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <algorithm>

std::vector<Movie> Recommender::recommend(int targetUserId, MovieManager& movieMgr, RatingManager& ratingMgr) {
    std::vector<Movie> recommendations;
    
    int bestUser = -1;
    int bestSim = -101;

    const std::vector<Rating>& allRatings = ratingMgr.getRatings();

    std::vector<int> allUsers;
    for (const auto& r : allRatings) {
        int uid = r.getUserId();
        if (std::find(allUsers.begin(), allUsers.end(), uid) == allUsers.end()) {
            allUsers.push_back(uid);
        }
    }

    std::vector<Rating> targetRatings;
    for (const auto& r : allRatings) {
        if (r.getUserId() == targetUserId) {
            targetRatings.push_back(r);
        }
    }

    for (int otherId : allUsers) {
        if (otherId == targetUserId) continue;

        std::vector<Rating> otherRatings;
        for (const auto& r : allRatings) {
            if (r.getUserId() == otherId) {
                otherRatings.push_back(r);
            }
        }

        int sim = SimilarityCalculator::calculate(targetRatings, otherRatings);
        if (sim > bestSim) {
            bestSim = sim;
            bestUser = otherId;
        }
    }

    if (bestUser == -1 || bestSim == -100) {
        return recommendations;
    }

    std::vector<Rating> bestUserRatings;
    for (const auto& r : allRatings) {
        if (r.getUserId() == bestUser) {
            bestUserRatings.push_back(r);
        }
    }

    for (const auto& r : bestUserRatings) {
        if (r.getScore() >= 4.0) {
            bool alreadySeen = false;
            for (const auto& myR : targetRatings) {
                if (myR.getMovieId() == r.getMovieId()) {
                    alreadySeen = true;
                    break;
                }
            }

            if (!alreadySeen) {
                Movie* m = movieMgr.findById(r.getMovieId());
                if (m != nullptr) {
                    recommendations.push_back(*m);
                }
            }
        }
    }

    return recommendations;
}