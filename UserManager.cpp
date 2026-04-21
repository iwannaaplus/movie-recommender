#include "UserManager.h"
#include <iostream>

void UserManager::addUser(const User& u) {
    users.push_back(u);
}

void UserManager::printAll() const {
    for (const User& u : users) {
        u.display();
        std::cout << std::endl;
    }
}