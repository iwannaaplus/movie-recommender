#pragma once
#include <string>
#include <iostream>

class User {
private:
    int id;
    std::string name;

public:
    User(int id, const std::string& name);
    
    int getId() const;
    std::string getName() const;

    friend std::ostream& operator<<(std::ostream& os, const User& user);
};