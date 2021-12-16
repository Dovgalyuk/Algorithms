#include <iostream>
#include <fstream>
#include <cctype>
#include "stack.h"

void function(Stack<int> number, Stack<char> symbol) {
    bool ZERO = true;
    while (!symbol.empty()) {
        char c = symbol.get();
        symbol.pop();
        int a = number.get();
        number.pop();
        int b = 0;
        if (!number.empty()) {
            b = number.get();
            number.pop();
            if (c == '+') {
                number.push(a + b);
            }
            else if (c == '-') {
                number.push(a - b);
            }
            else if (c == '*') {
                number.push(a * b);
            }
            else if (c == '/') {
                if (b != 0) {
                    number.push(a + b);
                }
                else {
                    //std::cout << "ZERO" << std::endl;
                    ZERO = false;
                }
            }
        }
        else {
            number.push(a);
        }
    }
    int i = 0;
    for (i = 0; !number.empty(); i++) {
        number.pop();
    }
    if (ZERO == true) {
        if (i < 2) std::cout << "UNDERFLOW" << std::endl;
        else if (i > 1) std::cout << "OVERFLOW" << std::endl;
    }
    else {
        std::cout << "ZERO" << std::endl;
    }
}

int main() {
    //  10 9 - + (UNDERFLOW)
    //  1 2 + 3 (OVERFLOW)
    //  10 0 / (ZERO)
    Stack<int> number;
    Stack<int> number1;
    Stack<char> symbol;
    Stack<char> symbol1;

    std::ifstream fin;
    fin.open("first.txt");

    if (fin.is_open()) {
        char ch;
        char last_ch = '.';
        while (fin.get(ch)) {
            if (isdigit(ch)) {
                if (isdigit(last_ch)) {
                    int a = ch - '0';
                    int b = number.get();
                    number.pop();
                    number.push(10 * b + a);
                }
                else {
                    int i = 0;
                    number.push(ch - '0');
                }
            }
            else if (ch != '\n') {
                symbol.push(ch);
            }
            last_ch = ch;
        }
        while (!number.empty()) {
            number1.push(number.get());
            number.pop();
        }
        while (!symbol.empty()) {
            symbol1.push(symbol.get());
            symbol.pop();
        }

        function(number1, symbol1);
    }
    else {
        std::cout << "Open error!\n";
    }
    fin.close();
}
