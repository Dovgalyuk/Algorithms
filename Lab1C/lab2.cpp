#include <iostream>
#include "stack.h"
#include <sstream>

int Calc(const std::string& str) {
    Stack* st = stack_create();
    std::istringstream iss(str);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stack_get(st);
            stack_pop(st);
            int a = stack_get(st);
            stack_pop(st);

            if (token == "+") stack_push(st, (a + b));
            else if (token == "-") stack_push(st, (a - b));
            else if (token == "*") stack_push(st, (a * b));
            else if (token == "/") stack_push(st, (a / b));
        }
        else stack_push(st, (std::stoi(token)));
    }
    int result = stack_get(st);
    stack_delete(st);
    return result;
}

int main() {
    std::string str;

    std::cout << "Input: ";
    std::getline(std::cin, str);

    int result = Calc(str);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
