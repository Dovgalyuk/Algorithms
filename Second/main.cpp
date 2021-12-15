#include <iostream>
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
    Stack<int> number;
    Stack<char> symbol;

    // 1 2 + 3
    number.push(3);
    symbol.push('+');
    number.push(2);
    number.push(1);
    function(number, symbol);

    Stack<int> number1;
    Stack<char> symbol1;

    //10 9 - +
    symbol1.push('+');
    symbol1.push('-');
    number1.push(9);
    number1.push(10);
    function(number1, symbol1);

    return 0;


    /*symbol1.push('/');
    number1.push(0);
    number1.push(10);
    function(number1, symbol1);
    return 0; */
}
