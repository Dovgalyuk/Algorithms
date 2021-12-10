//
// Created by onisken on 10.12.2021.
//

#include <iostream>
#include "stack.h"

int main() {
    int size = 0;
    std::cin >> size;

    Stack<int> stackPlus;
    Stack<int> stackMinus;
    /*
5
1 -
4 +
8 -
9 +
10 -
     */
    for (int i = 0; i < size; i++) {
        int tmp = 0;
        std::cin >> tmp;
        char tmpChar = '-';
        std::cin >> tmpChar;
        if (tmpChar == '+') {
            stackPlus.push(tmp);
        } else stackMinus.push(tmp);
    }

    int maxIndex = std::min(stackMinus.size(), stackPlus.size());

    Stack<int> order; // Storage minus

    for (int i = 0; i < maxIndex; i++) {
        int plus = stackPlus.get();
        int minus = stackMinus.get();

        if (plus > minus) {
            for (int j = 0; j < order.size(); j++) {
                int tmpMinus = order.get();
                if (plus > minus) continue;
                order.pop();
                stackPlus.pop();
                std::cout << plus << " " << tmpMinus << std::endl;
            }
            order.push(minus);
            stackMinus.pop();
        } else {
            for(;;) {
                order.push(minus);
                stackMinus.pop();
                if (plus < stackMinus.get()) minus = stackMinus.get();
                else break;
            }
            stackPlus.pop();
            std::cout << plus << " " << minus << std::endl;
        }
    }

    return 0;
}