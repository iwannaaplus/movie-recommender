#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

void showStatisticsMenu(const MovieManager& manager) {
    while (true) {
        std::cout << "\n=== 시스템 통계 메뉴 ===\n";
        std::cout << "1. 통계 화면 출력\n";
        std::cout << "2. CSV 파일로 내보내기\n";
        std::cout << "0. 돌아가기\n";
        std::cout << "선택 > ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n'); 

        try {
            if (choice == 0) return;
            if (choice == 1) {
                std::cout << "\n[전체 평균 평점] " << manager.getAverageRating() << std::endl;
                
                std::cout << "\n[장르별 평균 평점]\n";
                auto avgMap = manager.getAverageRatingByGenre();
                for (const auto& [genre, avg] : avgMap) {
                    std::cout << " - " << genre << ": " << avg << std::endl;
                }
                
                std::cout << "\n[Top 10 영화 목록]\n";
                auto topMovies = manager.getTopN(10);
                for (size_t i = 0; i < topMovies.size(); ++i) {
                    std::cout << " " << i + 1 << "위. " << topMovies[i] << std::endl;
                }
            }
            else if (choice == 2) {
                std::string outFilename;
                std::cout << "생성할 파일명 입력 (확장자 포함): ";
                std::cin >> outFilename;
                std::cin.ignore(10000, '\n'); 
                
                manager.exportStatisticsToCSV(outFilename);
                std::cout << outFilename << " 파일이 성공적으로 생성되었습니다." << std::endl;
            }
            else {
                std::cout << "잘못된 선택\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "오류: " << e.what() << std::endl;
        }
    }
}

int main() {
    MovieManager manager;
    UserManager userManager;
    RatingManager ratingManager;

    try {
        manager.loadFromFile("movies.csv");
        userManager.loadFromFile("users.csv");
        ratingManager.loadFromFile("ratings.csv");
    } catch (const std::exception& e) {
        std::cerr << "데이터 로드 오류: " << e.what() << std::endl;
    }

    int choice;

    while (true) {
        std::cout << "=== 영화 추천 시스템 ===" << std::endl;
        std::cout << "[ 영화 관리 ]" << std::endl;
        std::cout << "1. 신규 영화 등록" << std::endl;
        std::cout << "2. 영화 제목 검색" << std::endl;
        std::cout << "3. 전체 목록 출력 (기본)" << std::endl;
        std::cout << "4. 영화 정렬 출력 (평점순)" << std::endl;
        std::cout << "5. 영화 정렬 출력 (가나다순)" << std::endl;
        std::cout << "[ 사용자 관리 ]" << std::endl;
        std::cout << "6. 신규 사용자 등록" << std::endl;
        std::cout << "7. 전체 사용자 출력" << std::endl;
        std::cout << "[ 평점 관리 ]" << std::endl;
        std::cout << "8. 평점 등록" << std::endl;
        std::cout << "9. 전체 평점 내역 출력" << std::endl;
        std::cout << "[ 추천 및 분석 ]" << std::endl;
        std::cout << "10. 개인 맞춤 영화 추천" << std::endl;
        std::cout << "11. 시스템 통계 및 보고서 추출" << std::endl;
        std::cout << "0. 프로그램 종료" << std::endl;
        std::cout << "선택 > ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n'); 

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
            manager.sortByTitle();
            manager.printAll();
        }
        else if (choice == 6) {
            userManager.addUserFromInput();
        }
        else if (choice == 7) {
            userManager.printAll();
        }
        else if (choice == 8) {
            int uId, mId;
            double score;
            std::cout << "사용자 ID: "; std::cin >> uId;
            std::cout << "영화 ID: "; std::cin >> mId;
            std::cout << "평점 (0.0 ~ 5.0): "; std::cin >> score;
            std::cin.ignore(10000, '\n');

            try {
                userManager.findById(uId);
                manager.updateMovieRating(mId, score);
                ratingManager.addRating(Rating(uId, mId, score));
            } catch (const std::exception& e) {
                std::cout << "등록 실패: " << e.what() << std::endl;
            }
        }
        else if (choice == 9) {
            ratingManager.printAll();
        }
        else if (choice == 10) {
            int targetUid;
            std::cout << "추천 대상 사용자 ID 입력: ";
            std::cin >> targetUid;
            std::cin.ignore(10000, '\n');

            Recommender recommender(manager, ratingManager);
            std::vector<Movie> recs = recommender.recommend(targetUid);
            if (recs.empty()) {
                std::cout << "추천 가능한 내역이 없거나 유사 사용자를 찾을 수 없습니다." << std::endl;
            } else {
                std::cout << "=== 추천 영화 목록 ===" << std::endl;
                for (const auto& m : recs) {
                    std::cout << m << std::endl;
                }
            }
        }
        else if (choice == 11) {
            showStatisticsMenu(manager);
        }
        else {
            std::cout << "잘못된 선택입니다.\n";
        }

        std::cout << std::endl;
    }

    manager.saveToFile("movies.csv");
    userManager.saveToFile("users.csv");
    ratingManager.saveToFile("ratings.csv");

    return 0;
}