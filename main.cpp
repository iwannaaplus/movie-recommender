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
            int id, year;
            std::string title, genre;

            std::cout << "ID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "제목: ";
            std::getline(std::cin, title);

            std::cout << "장르: ";
            std::getline(std::cin, genre);

            std::cout << "연도: ";
            std::cin >> year;

            manager.addMovie(Movie(id, title, genre, year));
        }

        else if (choice == 2) {
            std::string title;
            std::cin.ignore();

            std::cout << "검색할 제목: ";
            std::getline(std::cin, title);

            Movie* m = manager.findByTitle(title);

            if (m != nullptr) m->display();
            else std::cout << "없음" << std::endl;
        }

        else if (choice == 3) {
            manager.printAll();
        }

        else if (choice == 4) {
            manager.sortByRating();
            manager.printAll();
        }

        else if (choice == 5) {
            int id;
            std::string name, email;

            std::cout << "ID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "이름: ";
            std::getline(std::cin, name);

            std::cout << "이메일: ";
            std::getline(std::cin, email);

            userManager.addUser(User(id, name, email));
        }

        else if (choice == 6) {
            userManager.printAll();
        }

        else if (choice == 7) {
            int userId, movieId;
            double score;

            std::cout << "사용자 ID: ";
            std::cin >> userId;
            std::cout << "영화 ID: ";
            std::cin >> movieId;
            std::cout << "평점: ";
            std::cin >> score;

            Rating r(userId, movieId, score);
            ratingManager.addRating(r);

            Movie* m = manager.findById(movieId);
            if (m != nullptr) {
                m->addRating(score);
            }
        }

        else if (choice == 8) {
            ratingManager.printAll();
        }

        std::cout << std::endl;
    }

    return 0;
}