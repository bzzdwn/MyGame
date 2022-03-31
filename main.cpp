#include <iostream>
#include "game_func.h"

int main() {
    int tmp = 1;
    while (tmp){
        system("cls");
start();
system("cls");
std::cout <<"Try again?" << '\n';
std::cout << "1 - Yes" << '\n';
std::cout << "0 - NO" << '\n';
std::cin >> tmp;
}
    return 0;
}
