#include "MovieManager.h"
#include "MovieConstants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <numeric>

void MovieManager::addMovie(const Movie& m) { movies.push_back(m); }

void MovieManager::printAll() const { 
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
    std::cout << "ID: "; std::cin >> id; std::cin.ignore(10000, '\n');
    std::cout << "제목: "; std::getline(std::cin, title);
    std::cout << "장르: "; std::getline(std::cin, genre);
    std::cout << "연도: "; std::cin >> year; std::cin.ignore(10000, '\n');
    addMovie(Movie(id, title, genre, year));
}

void MovieManager::searchMovie() {
    std::string title;
    std::cin.ignore(10000, '\n');
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

    movies.clear();
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;

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
        } catch (...) {
            continue;
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

double MovieManager::getAverageRating() const {
    if (movies.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& m : movies) {
        sum += m.getAverageRating();
    }
    return sum / movies.size();
}

std::map<std::string, double> MovieManager::getAverageRatingByGenre() const {
    std::map<std::string, double> sumByGenre;
    std::map<std::string, int> countByGenre;

    for (const auto& movie : movies) {
        if (movie.getGenre().empty()) continue;
        sumByGenre[movie.getGenre()] += movie.getAverageRating();
        countByGenre[movie.getGenre()]++;
    }

    std::map<std::string, double> avgByGenre;
    for (const auto& [genre, sum] : sumByGenre) {
        if (countByGenre[genre] > 0) {
            avgByGenre[genre] = sum / countByGenre[genre];
        }
    }
    return avgByGenre;
}

std::vector<Movie> MovieManager::getTopN(int n) const {
    auto sorted = movies;
    std::sort(sorted.begin(), sorted.end(), [](const Movie& a, const Movie& b) {
        return a.getAverageRating() > b.getAverageRating();
    });

    if (n > static_cast<int>(sorted.size())) {
        n = sorted.size();
    }
    return std::vector<Movie>(sorted.begin(), sorted.begin() + n);
}

void MovieManager::exportStatisticsToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("통계 파일을 생성할 수 없습니다: " + filename);
    }

    file << "Metric,Key,Value" << std::endl;
    file << "System,AverageRating," << getAverageRating() << std::endl;

    auto avgGenre = getAverageRatingByGenre();
    for (const auto& [genre, avg] : avgGenre) {
        file << "GenreAverage," << genre << "," << avg << std::endl;
    }

    auto top10 = getTopN(10);
    for (size_t i = 0; i < top10.size(); ++i) {
        file << "Top10_Rank_" << i + 1 << "," << top10[i].getTitle() << "," << top10[i].getAverageRating() << std::endl;
    }

    file.flush();
    file.close();
}

void MovieManager::sortByTitle() {
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.getTitle() < b.getTitle();
    });
}