#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int abs(int n){
    if (n < 0){
        return n * (-1);
    }
    return n;
}

int precedence(char op) {
    if (op == '+') {
        return 1;
    }
    if (op == '-') {
        return -1;
    }
    if (op == '*') {
        return 2;
    }
    return 0;
}

void Operation(int op) {
    std::cout << "POP A" << std::endl;
    std::cout << "POP B" << std::endl;

    if (op == 1) {
        std::cout << "ADD A, B" << std::endl;
    }
    else if (op == -1) {
        std::cout << "SUB A, B" << std::endl;
    }
    else if (op == 2) {
        std::cout << "MUL A, B" << std::endl;
    }

    std::cout << "PUSH A" << std::endl;
}

// Main function 
void translate(const std::string& expr) {
    Stack* ops = stack_create();

    for (size_t i = 0; i < expr.size(); ++i) {
        char token = expr[i];
        if (token == ' ') {
            continue;
        }
        if (isdigit(token)) {
            int value = 0;
            while (i < expr.size() && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                ++i;
            }
            --i;

            std::cout << "PUSH " << value << std::endl;
        }
        else if (token == '(') {
            stack_push(ops, 0);
        }
        else if (token == ')') {
            if (!stack_empty(ops)) {
                while (stack_get(ops) != 0) 
                {
                    Operation(stack_get(ops));
                    stack_pop(ops);
                }
                stack_pop(ops);
            }
        }
        else if (token == '+' || token == '*' || token == '-')
        {
            while (!stack_empty(ops) && (abs(stack_get(ops)) >= abs(precedence(token)))) {
                Operation(stack_get(ops));
                stack_pop(ops);
            }
            stack_push(ops, precedence(token));
        }
    }

    while (!stack_empty(ops)) {
        Operation(stack_get(ops));
        stack_pop(ops);
    }

    stack_delete(ops);
}

int main(int argc, char** argv) {
    if (argc > 1)
    {
        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            std::cerr << "Failed to open input file: " << "\n";
            return 1;
        }

        size_t n;
        input >> n;

        while (n-- > 0)
        {
            std::string s;
            input >> s;
            translate(s);
        }

        input.close();
        return 0;
    }
    else {
        throw std::runtime_error("Invalid arguments");
    }
}