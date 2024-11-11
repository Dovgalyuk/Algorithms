#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
#define first_op 1
#define second_op 2
#define staple 0

int abs(int n){
    if (n < 0){
        return -n;
    }
    return n;
}

int precedence(char op) {
    if (op == '+') {
        return first_op;
    }
    if (op == '-') {
        return -first_op;
    }
    if (op == '*') {
        return second_op;
    }
    return 0;
}

void Operation(int op) {
    std::cout << "POP A" << std::endl;
    std::cout << "POP B" << std::endl;

    if (op == first_op) {
        std::cout << "ADD A, B" << std::endl;
    }
    else if (op == -first_op) {
        std::cout << "SUB A, B" << std::endl;
    }
    else if (op == second_op) {
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
            stack_push(ops, staple);
        }
        else if (token == ')') {
            if (!stack_empty(ops)) {
                while (stack_get(ops) != staple)
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