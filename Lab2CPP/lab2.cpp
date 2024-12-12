#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

bool is_balanced(const std::string& str) {
    Stack* stack = stack_create();

    for (char c : str) {
        if (c == '(' || c == '"' || c == '\'') {
            if (!stack_empty(stack) && stack_get(stack) == c && (c == '"' || c == '\'')) {
                stack_pop(stack);
            } else {
                stack_push(stack, static_cast<Data>(c));
            }
        } else if (c == ')') {
            // на закрывающую скобку
            if (stack_empty(stack) || stack_get(stack) != '(') {
                stack_delete(stack);
                return false;
            }
            stack_pop(stack);
        }
    }
    bool balanced = stack_empty(stack);
    stack_delete(stack);
    return balanced;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.txt>\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    std::ofstream outfile(argv[2]);
    std::string s;

    while (std::getline(infile, s)) {
        if (is_balanced(s)) {
            outfile << "YES" << std::endl;
        } else {
            outfile << "NO" << std::endl;
        }
    }

    return 0;
}