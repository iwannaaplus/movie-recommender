#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <algorithm>
#include <set>
#include <map>

Recommender::Recommender(MovieManager& mMgr, RatingManager& rMgr) 
    : movieMgr(mMgr), ratingMgr(rMgr) {}

std::vector<Movie> Recommender::recommend(int targetUserId) {
    std::vector<Movie> recommendations;
    const std::vector<Rating>& allRatings = ratingMgr.getRatings();

    std::vector<Rating> myRatings;
    std::set<int> myMovieIds;
    for (const auto& r : allRatings) {
        if (r.getUserId() == targetUserId) {
            myRatings.push_back(r);
            myMovieIds.insert(r.getMovieId());
        }
    }

    if (myRatings.empty()) {
        return recommendations;
    }

    std::vector<int> allUsers;
    for (const auto& r : allRatings) {
        int uid = r.getUserId();
        if (uid != targetUserId && std::find(allUsers.begin(), allUsers.end(), uid) == allUsers.end()) {
            allUsers.push_back(uid);
        }
    }

    std::vector<std::pair<int, int>> similarities;
    for (int otherId : allUsers) {
        std::vector<Rating> otherRatings;
        for (const auto& r : allRatings) {
            if (r.getUserId() == otherId) {
                otherRatings.push_back(r);
            }
        }

        int sim = SimilarityCalculator::Similaritycalculate(myRatings, otherRatings);
        if (sim != -100) {
            similarities.push_back({otherId, sim});
        }
    }

    if (similarities.empty()) {
        return recommendations;
    }

    std::sort(similarities.begin(), similarities.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    });

    size_t K = 3; 
    size_t neighborsCount = std::min(K, similarities.size());

    std::map<int, double> movieScores;

    for (size_t i = 0; i < neighborsCount; ++i) {
        int neighborId = similarities[i].first;
        for (const auto& r : allRatings) {
            if (r.getUserId() == neighborId) {
                if (myMovieIds.find(r.getMovieId()) == myMovieIds.end()) {
                    movieScores[r.getMovieId()] += r.getScore();
                }
            }
        }
    }

    if (movieScores.empty()) {
        return recommendations;
    }

    std::vector<std::pair<int, double>> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        return a.second > b.second;
    });

    for (const auto& pair : sortedMovies) {
        Movie* m = movieMgr.findById(pair.first);
        if (m != nullptr) {
            recommendations.push_back(*m);
        }
    }

    return recommendations;
}