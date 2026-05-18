#pragma once
#include <vector>
#include <string>
#include "Rating.h"
#include "MovieManager.h"
#include "BaseManager.h"

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;

public:
    void addRating(const Rating& r);
    void printAll() const;

    void addRatingFromInput(MovieManager& manager);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};