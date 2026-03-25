#include "User.h"
#include <iostream>
using namespace std;

User::User(int id, string name, string email)
    : id(id), name(name), email(email) {}

int User::getId() const {
    return id;
}

string User::getName() const {
    return name;
}

string User::getEmail() const {
    return email;
}

void User::display() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
}