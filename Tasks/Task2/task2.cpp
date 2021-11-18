#include <iostream>
#include "stack.h"
#include <string>

const char BACKSPACE = '#';

int main() {
    Stack<char> stack;
    std::string str;
    std::cin >> str;
    for (char ch : str) {
        if (ch == BACKSPACE) {
            stack.pop();
        } else {
            stack.push(ch);
        }
    }
    str.clear();
    while (!stack.empty()) {
        str = stack.get() + str;
        stack.pop();
    }
    std::cout << str;
    return 0;
}