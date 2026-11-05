#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

void task1(const std::string& str) {
    Stack* stack = stack_create();
    bool has_brackets = false;

    for (char c : str) {
        if (c == '(' || c == ')' || c == '[' || c == ']' ||
            c == '{' || c == '}' || c == '"' || c == '\'') {

            has_brackets = true;

            if (c == '(' || c == '[' || c == '{' || c == '"' || c == '\'') {
                if ((c == '"' || c == '\'') && !stack_empty(stack) && (char)stack_get(stack) == c) {
                    stack_pop(stack);
                } else {
                    stack_push(stack, c);
                }
            }
            else if (c == ')' || c == ']' || c == '}') {
                if (stack_empty(stack) ||
                    (c == ')' && (char)stack_get(stack) != '(') ||
                    (c == ']' && (char)stack_get(stack) != '[') ||
                    (c == '}' && (char)stack_get(stack) != '{')) {

                    std::cout << "NO\n";
                    stack_delete(stack);
                    return;
                    }
                stack_pop(stack);
            }
            }
    }

    if (!has_brackets) {
        std::cout << "ERROR\n";
    }
    else if (!stack_empty(stack)) {
        std::cout << "NO\n";
    }
    else {
        std::cout << "YES\n";
    }

    stack_delete(stack);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "ERROR\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cout << "ERROR\n";
        return 1;
    }

    std::string line;
    if (std::getline(input, line)) {
        task1(line);
    } else {
        std::cout << "ERROR\n";
    }

    return 0;
}