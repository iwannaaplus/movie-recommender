#include <iostream>
#include <vector>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
using namespace std;

int main() {
    vector<Movie> movies;

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

    cout << "=== Movie List ===" << endl;
    for (int i = 0; i < movies.size(); i++) {
        movies[i].display();
        cout << endl;
    }

    cout << "=== User Info ===" << endl;
    u1.display();
    cout << endl;
    u2.display();
    cout << endl;

    cout << "=== Rating Info ===" << endl;
    r1.display();
    cout << endl;
    r2.display();
    cout << endl;
    r3.display();

    return 0;
}