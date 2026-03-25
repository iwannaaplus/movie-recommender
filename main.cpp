#include <iostream>
#include <vector>
#include "Movie.h"
#include "User.h"
#include "Rating.h"

int main() {
    std::vector<Movie> movies;

    Movie m1(1, "Inception", "SF", 2010);
    Movie m2(2, "Parasite", "Thriller", 2019);

    movies.push_back(m1);
    movies.push_back(m2);

    User u1(101, "Kim", "kim@example.com");
    User u2(102, "Lee", "lee@example.com");

    Rating r1(101, 1, 4.5);
    Rating r2(102, 1, 5.0);
    Rating r3(101, 2, 4.0);

    movies[0].addRating(r1.getScore());
    movies[0].addRating(r2.getScore());
    movies[1].addRating(r3.getScore());

    std::cout << "=== Movie List ===" << std::endl;
    for (int i = 0; i < movies.size(); i++) {
        movies[i].display();
        std::cout << std::endl;
    }

    std::cout << "=== User Info ===" << std::endl;
    u1.display();
    std::cout << std::endl;
    u2.display();
    std::cout << std::endl;

    std::cout << "=== Rating Info ===" << std::endl;
    r1.display();
    std::cout << std::endl;
    r2.display();
    std::cout << std::endl;
    r3.display();

    return 0;
}