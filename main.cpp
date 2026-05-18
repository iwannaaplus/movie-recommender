#include <iostream>
#include <string>
#include <vector>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

int main() {
    MovieManager manager;
    UserManager userManager;
    RatingManager ratingManager;

    manager.loadFromFile("movies.csv");
    userManager.loadFromFile("users.csv");
    ratingManager.loadFromFile("ratings.csv");

    int choice;

    while (true) {
        std::cout << "=== Movie Recommender ===" << std::endl;
        std::cout << "[ 영화 ]" << std::endl;
        std::cout << "1. 영화 추가" << std::endl;
        std::cout << "2. 제목 검색" << std::endl;
        std::cout << "3. 전체 출력" << std::endl;
        std::cout << "4. 평점순 출력" << std::endl;
        std::cout << "[ 사용자 ]" << std::endl;
        std::cout << "5. 사용자 추가" << std::endl;
        std::cout << "6. 사용자 출력" << std::endl;
        std::cout << "[ 평점 ]" << std::endl;
        std::cout << "7. 평점 입력" << std::endl;
        std::cout << "8. 평점 출력" << std::endl;
        std::cout << "[ 추천 ]" << std::endl;
        std::cout << "9. 개인 맞춤 영화 추천" << std::endl;
        std::cout << "0. 종료" << std::endl;
        std::cout << "선택 > ";

        std::cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            manager.addMovieFromInput();
        }
        else if (choice == 2) {
            manager.searchMovie();
        }
        else if (choice == 3) {
            manager.printAll();
        }
        else if (choice == 4) {
            manager.sortByRating();
            manager.printAll();
        }
        else if (choice == 5) {
            userManager.addUserFromInput();
        }
        else if (choice == 6) {
            userManager.printAll();
        }
        else if (choice == 7) {
            ratingManager.addRatingFromInput();
        }
        else if (choice == 8) {
            ratingManager.printAll();
        }
        else if (choice == 9) {
            int targetUid;
            std::cout << "추천을 받을 사용자 ID 입력: ";
            std::cin >> targetUid;

            Recommender recommender(manager, ratingManager);
            std::vector<Movie> recs = recommender.recommend(targetUid);
            if (recs.empty()) {
                std::cout << "추천할 만한 영화가 없거나 비슷한 사용자를 찾을 수 없습니다." << std::endl;
            } else {
                std::cout << "=== [추천 리스트] ===" << std::endl;
                for (const auto& m : recs) {
                    std::cout << m << std::endl;
                }
            }
        }

        std::cout << std::endl;
    }

    manager.saveToFile("movies.csv");
    userManager.saveToFile("users.csv");
    ratingManager.saveToFile("ratings.csv");

    return 0;
}