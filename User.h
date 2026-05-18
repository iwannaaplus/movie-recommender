#pragma once
#include <string>

class User {
private:
    int id;
    std::string name;
    std::string email;

public:
    User(); // 컴파일 안정성을 위한 기본 생성자 추가
    User(int id, std::string name, std::string email);

    int getId() const;
    std::string getName() const;
    std::string getEmail() const;

    void display() const;
};