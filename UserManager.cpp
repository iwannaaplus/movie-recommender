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

void UserManager::addUserFromInput() {
    int id;
    std::string name, email;

    std::cout << "ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "이름: ";
    std::getline(std::cin, name);

    std::cout << "이메일: ";
    std::getline(std::cin, email);

    addUser(User(id, name, email));
}

void UserManager::loadFromFile(const std::string& filename) {
}

void UserManager::saveToFile(const std::string& filename) const {
}

int UserManager::size() const {
    return users.size();
}