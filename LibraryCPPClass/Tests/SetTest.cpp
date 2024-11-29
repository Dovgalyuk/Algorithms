#include <iostream>
#include <string>
#include "Set.h"

int basicTest() {
    Set set;

    set.insert("A");
    set.insert("B");
    set.insert("C");

    if (set.find("A") == nullptr) {
        std::cout << "Invalid insertion - 1" << std::endl;
        return 1;
    }

    if (set.find("B") == nullptr) {
        std::cout << "Invalid insertion - 2" << std::endl;
        return 2;
    }

    if (set.find("C") == nullptr) {
        std::cout << "Invalid insertion - 3" << std::endl;
        return 3;
    }

    if (set.find("D") != nullptr) {
        std::cout << "Invalid insertion and seraching - 4" << std::endl;
        return 4;
    }

    set.remove("B");
    if (set.find("B") != nullptr) {
        std::cout << "Invalid removing - 5" << std::endl;
        return 5;
    }

    return 0;
}

void performanceTest() {
    Set set;

    for (int i = 1; i <= 1e6; ++i) {
        set.insert(std::to_string(i));
    }

    for (int i = 1; i <= 1e6; ++i) {
        if (set.find(std::to_string(i))->data != std::to_string(i)) {
            std::cout << "ERROR!";
        }
    }

    for (int i = 1; i <= 1e6; ++i) {
        set.remove(std::to_string(i));
    }
}

int main()
{
    int res = basicTest();
    if (res) return res;
    performanceTest();

    std::cout << "All tests was passed!" << std::endl;

    return 0;
}