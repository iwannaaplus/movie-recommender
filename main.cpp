#include <iostream>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"
#include "UserManager.h"

int main() {
    MovieManager manager;
    UserManager userManager;

    Movie m1(1, "Inception", "SF", 2010);
    Movie m2(2, "Parasite", "Thriller", 2019);

    manager.addMovie(m1);
    manager.addMovie(m2);

    userManager.addUser(User(101, "Kim", "kim@example.com"));
    userManager.addUser(User(102, "Lee", "lee@example.com"));

    Rating r1(101, 1, 4.5);
    Rating r2(102, 1, 5.0);
    Rating r3(101, 2, 4.0);

    Movie* movie1 = manager.findByTitle("Inception");
    Movie* movie2 = manager.findByTitle("Parasite");

    if (movie1 != nullptr) {
        movie1->addRating(r1.getScore());
        movie1->addRating(r2.getScore());
    }

    if (movie2 != nullptr) {
        movie2->addRating(r3.getScore());
    }

    std::cout << "=== Movie List ===" << std::endl;
    manager.printAll();
    std::cout << std::endl;

    std::cout << "=== User Info ===" << std::endl;
    userManager.printAll();

    std::cout << std::endl;

    std::cout << "=== Rating Info ===" << std::endl;
    r1.display();
    std::cout << std::endl;
    r2.display();
    std::cout << std::endl;
    r3.display();

    return 0;
}