#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

void UserManager::addUser(const User& u) { users.push_back(u); }

void UserManager::printAll() const {
    for (const auto& u : users) {
        std::cout << u << std::endl;
    }
}

User& UserManager::findById(int id) {
    for (User& u : users) {
        if (u.getId() == id) return u;
    }
    throw std::out_of_range("해당 ID의 사용자를 찾을 수 없습니다: " + std::to_string(id));
}

void UserManager::addUserFromInput() {
    int id;
    std::string name;
    
    std::cout << "사용자 ID: "; 
    std::cin >> id; 
    std::cin.ignore(10000, '\n');
    
    std::cout << "이름: "; 
    std::getline(std::cin, name);
    
    users.push_back(User(id, name));
}

void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
    }

    users.clear();
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line.back() == '\r') line.pop_back(); 
        if (line.empty()) continue;

        try {
            std::stringstream ss(line);
            std::string token;

            std::getline(ss, token, ','); int id = std::stoi(token);
            std::getline(ss, token, ','); std::string name = token;

            users.push_back(User(id, name));
        } catch (...) {
            continue;
        }
    }
    file.close();
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    
    file << "id,name" << std::endl; 
    for (const auto& u : users) {
        file << u.getId() << "," << u.getName() << std::endl;
    }
    file.close();
}

int UserManager::size() const { return users.size(); }