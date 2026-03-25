#include "User.h"
#include <iostream>

User::User(int id, std::string name, std::string email)
    : id(id), name(name), email(email) {}

int User::getId() const {
    return id;
}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}

void User::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
}