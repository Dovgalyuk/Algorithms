#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

int get_priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool is_valid_character(char c) {
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        c == '+' || c == '-' || c == '*' || c == '/' ||
        c == '(' || c == ')' ||
        c == ' ' || c == '\t';
}

std::string infix_to_postfix(const std::string& infix) {
    if (infix.empty()) {
        return "error";
    }

    Stack* stack = stack_create();
    std::string postfix;

    for (char c : infix) {
        if (c == ' ' || c == '\t') continue;

        if (!is_valid_character(c)) {
            stack_delete(stack);
            return "error";
        }

        if (isalpha(c)) {
            postfix += c;
        }
        else if (c == '(') {
            stack_push(stack, c);
        }
        else if (c == ')') {
            while (!stack_empty(stack) && stack_get(stack) != '(') {
                postfix += stack_get(stack);
                stack_pop(stack);
            }
            if (stack_empty(stack)) {
                stack_delete(stack);
                return "error";
            }
            stack_pop(stack);
        }
        else {
            while (!stack_empty(stack) &&
                get_priority(stack_get(stack)) >= get_priority(c) &&
                stack_get(stack) != '(') {
                postfix += stack_get(stack);
                stack_pop(stack);
            }
            stack_push(stack, c);
        }
    }

    while (!stack_empty(stack)) {
        if (stack_get(stack) == '(') {
            stack_delete(stack);
            return "error";
        }
        postfix += stack_get(stack);
        stack_pop(stack);
    }

    stack_delete(stack);

    if (postfix.empty()) {
        return "error";
    }

    return postfix;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cout << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    std::string expression;
    std::getline(input, expression);

    std::string postfix = infix_to_postfix(expression);
    std::cout << postfix << std::endl;

    return 0;
}