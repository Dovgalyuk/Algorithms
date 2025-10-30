#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stack.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0;
}

std::vector<std::string> generate_commands(const std::string& expr) {
    std::vector<std::string> postfix;
    Stack* op_stack = stack_create();

    for (char c : expr) {
        if (isdigit(c)) {
            postfix.push_back(std::string(1, c));
        }
        else if (c == '+' || c == '-' || c == '*') {
            while (!stack_empty(op_stack) && precedence((char)stack_get(op_stack)) >= precedence(c)) {
                postfix.push_back(std::string(1, (char)stack_get(op_stack)));
                stack_pop(op_stack);
            }
            stack_push(op_stack, c);
        }
        else if (c == '(') {
            stack_push(op_stack, c);
        }
        else if (c == ')') {
            while (!stack_empty(op_stack) && (char)stack_get(op_stack) != '(') {
                postfix.push_back(std::string(1, (char)stack_get(op_stack)));
                stack_pop(op_stack);
            }
            if (!stack_empty(op_stack)) stack_pop(op_stack);
        }
    }
    while (!stack_empty(op_stack)) {
        postfix.push_back(std::string(1, (char)stack_get(op_stack)));
        stack_pop(op_stack);
    }
    stack_delete(op_stack);

    std::vector<std::string> commands;
    for (const auto& token : postfix) {
        if (isdigit(token[0])) {
            commands.push_back("PUSH " + token);
        }
        else {
            commands.push_back("POP A");
            commands.push_back("POP B");
            if (token == "+") {
                commands.push_back("ADD A, B");
            }
            else if (token == "-") {
                commands.push_back("SUB A, B");
            }
            else if (token == "*") {
                commands.push_back("MUL A, B");
            }
            commands.push_back("PUSH A");
        }
    }
    return commands;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    std::string expr;
    std::getline(input, expr);
    input.close();

    auto commands = generate_commands(expr);
    for (const auto& cmd : commands) {
        std::cout << cmd << std::endl;
    }

    return 0;
}
