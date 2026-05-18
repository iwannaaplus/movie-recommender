#pragma once
#include <string>

class Rating {
private:
    int userId;
    int movieId;
    double score;

public:
    Rating(); // 컴파일 안정성을 위한 기본 생성자 추가
    Rating(int userId, int movieId, double score);

    int getUserId() const;
    int getMovieId() const;
    double getScore() const;

    void display() const;
};