//
// Created by onisken on 10.12.2021.
//

#include <iostream>
#include "stack.h"

int main() {
    int size = 0;
    std::cin >> size;
    /*
5
1 -
4 +
8 -
9 +
10 -
     */
    Stack<int> order; // Storage minus
    for (int i = 0; i < size; i++) {
        int tmp = 0;
        std::cin >> tmp;
        char tmpChar;
        std::cin >> tmpChar;
        if (tmpChar == '-') {
            if (order.size() <= 0) continue;

            const int plus = order.get();
            if (tmp < plus) continue;

            std::cout << plus << " " << tmp << std::endl;
            order.pop();
        } else order.push(tmp);
    }
    return 0;
}