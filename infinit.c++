#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include "bigcub.h++"

int main() {
    BigCub a(2);
    size_t oldSize = 0;
    std::time_t time;
    std::tm tm;

    while (1) {
        a *= a;
        time = std::time(nullptr);
        tm = *std::localtime(&time);
        std::cout << std::put_time(&tm, "%c") << ": " << a.size() << std::endl;
    }
}
