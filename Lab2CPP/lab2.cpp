#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "stack.h"

void befunge_interpret(const std::string& program) {
    Stack* stack = stack_create();
    srand(static_cast<unsigned int>(time(nullptr)));

    for (char c : program) {
        if (std::isdigit(c)) {
            stack_push(stack, c - '0');
        }
        else if (c == '+') {
            if (!stack_empty(stack)) {
                Data b = stack_get(stack); stack_pop(stack);
                if (!stack_empty(stack)) {
                    Data a = stack_get(stack); stack_pop(stack);
                    stack_push(stack, a + b);
                }
                else {
                    stack_push(stack, b);
                }
            }
        }
        else if (c == '-') {
            if (!stack_empty(stack)) {
                Data b = stack_get(stack); stack_pop(stack);
                if (!stack_empty(stack)) {
                    Data a = stack_get(stack); stack_pop(stack);
                    stack_push(stack, a - b);
                }
                else {
                    stack_push(stack, -b);
                }
            }
        }
        else if (c == '*') {
            if (!stack_empty(stack)) {
                Data b = stack_get(stack); stack_pop(stack);
                if (!stack_empty(stack)) {
                    Data a = stack_get(stack); stack_pop(stack);
                    stack_push(stack, a * b);
                }
                else {
                    stack_push(stack, 0);
                }
            }
        }
        else if (c == '/') {
            if (!stack_empty(stack)) {
                Data b = stack_get(stack); stack_pop(stack);
                if (!stack_empty(stack)) {
                    Data a = stack_get(stack); stack_pop(stack);
                    if (b != 0) {
                        stack_push(stack, a / b);
                    }
                    else {
                        stack_push(stack, 0);
                    }
                }
                else {
                    stack_push(stack, 0);
                }
            }
        }
        else if (c == '%') {
            if (!stack_empty(stack)) {
                Data b = stack_get(stack); stack_pop(stack);
                if (!stack_empty(stack)) {
                    Data a = stack_get(stack); stack_pop(stack);
                    if (b != 0) {
                        stack_push(stack, a % b);
                    }
                    else {
                        stack_push(stack, 0);
                    }
                }
                else {
                    stack_push(stack, 0);
                }
            }
        }
        else if (c == '!') {
            if (!stack_empty(stack)) {
                Data a = stack_get(stack); stack_pop(stack);
                stack_push(stack, a == 0 ? 1 : 0);
            }
            else {
                stack_push(stack, 1);
            }
        }
        else if (c == '`') {
            if (!stack_empty(stack)) {
                Data b = stack_get(stack); stack_pop(stack);
                if (!stack_empty(stack)) {
                    Data a = stack_get(stack); stack_pop(stack);
                    stack_push(stack, a > b ? 1 : 0);
                }
                else {
                    stack_push(stack, 0);
                }
            }
        }
        else if (c == ':') {
            if (!stack_empty(stack)) {
                Data a = stack_get(stack);
                stack_push(stack, a);
            }
            else {
                stack_push(stack, 0);
            }
        }
        else if (c == '.') {
            if (!stack_empty(stack)) {
                Data a = stack_get(stack); stack_pop(stack);
                std::cout << a << std::endl;
            }
        }
        else if (c == '&') {
            stack_push(stack, rand() % 100);
        }
    }

    stack_delete(stack);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <program_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::string program;
    std::string line;
    while (std::getline(file, line)) {
        program += line;
    }

    befunge_interpret(program);

    return 0;
}