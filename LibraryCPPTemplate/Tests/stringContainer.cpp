#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "stringContainer.h"

typedef StringContainer MyContainer;

int main() {
    MyContainer* container = new MyContainer;

    if (!container) {
        std::cout << "Container not created\n";
        return 1;
    }

    container->insert("apple");
    container->insert("banana");
    container->insert("cherry");

    *container = *container;

    if (!container->find("apple")) {
        std::cout << "Insert|find error\n";
        return 1;
    }

    if (container->find("anksjdnakj")) {
        std::cout << "Find error\n";
        return 1;
    }

    container->remove("banana");
    if (container->find("banana")) {
        std::cout << "Remove error\n";
        return 1;
    }

    MyContainer copy(*container);
    if (!copy.find("cherry")) {
        std::cout << "Copy error\n";
        return 1;
    }

    // Нагрузучное тестирование
    delete container;
    container = new MyContainer;

    const int N = 10000;
    for (int i = 0; i < N; ++i) {
        std::string s = std::to_string(i);
        while (s.length() < 6) s = "0" + s;
        container->insert(s);
    }

    int height = container->get_height();
    double limit = 2.0 * std::log2(N);

    if (height > limit) {
        std::cout << "Load test error: complesity to big\n";
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        std::string s = std::to_string(i);
        while (s.length() < 6) s = "0" + s;

        if (!container->find(s)) {
            std::cout << "Load test error: element not find\n";
            return 1;
        }
    }

    std::cout << "Tests passed\n";

    delete container;
    return 0;
}

