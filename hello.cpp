#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "=== 영화 추천 시스템 ===" << std::endl;
    std::cout << "이름 입력: ";
    std::getline(std::cin, name);
    std::cout << name << "님, 환영합니다!" << std::endl;
    return 0;
}