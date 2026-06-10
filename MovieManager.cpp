#include "MovieManager.h"
#include "MovieConstants.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

void MovieManager::addMovie(const Movie& m) { movies.push_back(m); }

void MovieManager::printAll() const {
    Timer t("printAll");
    for (const auto& m : movies) {
        std::cout << m << std::endl;
    }
}

Movie& MovieManager::findByTitle(const std::string& title) {
    for (Movie& m : movies) {
        if (m.getTitle() == title) return m;
    }
    throw std::out_of_range("해당 제목의 영화를 찾을 수 없습니다: " + title);
}

Movie& MovieManager::findById(int id) {
    for (Movie& m : movies) {
        if (m.getId() == id) return m;
    }
    throw std::out_of_range("해당 ID의 영화를 찾을 수 없습니다: " + std::to_string(id));
}

void MovieManager::sortByRating() { std::sort(movies.begin(), movies.end()); }

void MovieManager::addMovieFromInput() {
    int id, year;
    std::string title, genre;
    std::cout << "ID: "; std::cin >> id; std::cin.ignore();
    std::cout << "제목: "; std::getline(std::cin, title);
    std::cout << "장르: "; std::getline(std::cin, genre);
    std::cout << "연도: "; std::cin >> year;
    addMovie(Movie(id, title, genre, year));
}

void MovieManager::searchMovie() {
    Timer t("searchMovie");
    std::string title;
    std::cin.ignore();
    std::cout << "검색할 제목: ";
    std::getline(std::cin, title);

    try {
        Movie& m = findByTitle(title);
        std::cout << m << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "없음 (" << e.what() << ")" << std::endl;
    }
}

void MovieManager::updateMovieRating(int movieId, double score) {
    try {
        Movie& m = findById(movieId);
        m.addRating(score);
    } catch (const std::out_of_range& e) {
        std::cerr << "오류: " << e.what() << std::endl;
    }
}

void MovieManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
    }

    std::string line;
    std::getline(file, line);
    int lineNum = 1;

    while (std::getline(file, line)) {
        lineNum++;
        try {
            std::stringstream ss(line);
            std::string token;

            std::getline(ss, token, ','); int id = std::stoi(token);
            std::getline(ss, token, ','); std::string title = token;
            std::getline(ss, token, ','); std::string genre = token;
            std::getline(ss, token, ','); int year = std::stoi(token);
            std::getline(ss, token, ','); double totalRating = std::stod(token);
            std::getline(ss, token, ','); int ratingCount = std::stoi(token);

            movies.push_back(Movie(id, title, genre, year, totalRating, ratingCount));
        } catch (const std::invalid_argument& e) {
            std::cerr << lineNum << "번 줄 데이터 파싱 오류로 건너뜀: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << lineNum << "번 줄 숫자 범위 초과로 건너뜀: " << e.what() << std::endl;
        }
    }
    file.close();
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    file << "id,title,genre,year,totalRating,ratingCount" << std::endl;
    for (const auto& m : movies) {
        file << m.getId() << "," << m.getTitle() << "," << m.getGenre() << ","
             << m.getReleaseYear() << "," << m.totalRatingValue() << "," << m.ratingCountValue() << std::endl;
    }
    file.close();
}

int MovieManager::size() const { return movies.size(); }