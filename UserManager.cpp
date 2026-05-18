#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int id = std::stoi(token);

        std::getline(ss, token, ',');
        std::string name = token;

        std::getline(ss, token, ',');
        std::string email = token;

        users.push_back(User(id, name, email));
    }
    file.close();
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "id,name,email" << std::endl;
    for (const auto& u : users) {
        file << u.getId() << ","
             << u.getName() << ","
             << u.getEmail() << std::endl;
    }
    file.close();
}

int UserManager::size() const {
    return users.size();
}