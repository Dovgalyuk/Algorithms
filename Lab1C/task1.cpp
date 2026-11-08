#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

bool is_matching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

void task1(const std::string& str) {
    Stack* stack = stack_create();
    bool has_brackets = false;

    for (char c : str) {
        if (c == '(' || c == '[' || c == '{') {
            has_brackets = true;
            stack_push(stack, c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            has_brackets = true;
            if (stack_empty(stack) || !is_matching((char)stack_get(stack), c)) {
                std::cout << "NO\n";
                stack_delete(stack);
                return;
            }
            stack_pop(stack);
        }
        else if (c == '"' || c == '\'') {
            has_brackets = true;
            if (!stack_empty(stack) && (char)stack_get(stack) == c) {
                stack_pop(stack);
            } else {
                stack_push(stack, c);
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
    if (argc != 2) {
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
