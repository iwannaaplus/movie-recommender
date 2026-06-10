#include "User.h"

User::User(int id, const std::string& name) : id(id), name(name) {}

int User::getId() const { return id; }

std::string User::getName() const { return name; }

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.id << "," << user.name;
    return os;
}