#include <iostream>
#include <string>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"

int main() {
    MovieManager manager;
    UserManager userManager;
    RatingManager ratingManager;

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

        std::cout << std::endl;
    }

    return 0;
}