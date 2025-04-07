#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

std::string check_balance(const std::string &input) {
    Stack *stack = stack_create();
    std::vector<char> quote_stack; 
    
    std::unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char ch : input) {
        if (ch == '"' || ch == '\'') {
            if (quote_stack.empty() || quote_stack.back() != ch) {
                quote_stack.push_back(ch);
            } else {
                quote_stack.pop_back();
            }
        }

        if (ch == '(' || ch == '[' || ch == '{') {
            stack_push(stack, ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack_empty(stack)) {
                stack_delete(stack);
                return "NO";
            }

            char top = stack_get(stack);
            stack_pop(stack);

            if (top != pairs[ch]) {
                stack_delete(stack);
                return "NO";
            }
        }
    }

    bool result = stack_empty(stack) && quote_stack.empty();
    stack_delete(stack);
    
    return result ? "YES" : "NO";
}

int main(int argc, char *argv[]) {
    std::string input;

    if (argc > 1) {
        std::ifstream input_file(argv[1]);
        if (input_file.is_open()) {
            std::getline(input_file, input);
            input_file.close();
        } else {
            std::cerr << "Не удалось открыть файл " << argv[1] << ". Введите данные вручную:\n";
            std::getline(std::cin, input);
        }
    } else {
        std::cerr << "Файл не передан. Введите данные вручную:\n";
        std::getline(std::cin, input);
    }

    std::cout << check_balance(input) << std::endl;

    return 0;
}