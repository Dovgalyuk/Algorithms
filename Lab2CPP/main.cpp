#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdlib>

std::string check_balance(const std::string &input) {
    Stack *stack = stack_create();
    
    std::unordered_map<char, char> pairs = 
    {
        {')', '('},
        {']', '['},
        {'}', '{'},
        {'"', '"'}
    };

    for (char ch : input) 
    {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '"') {
            stack_push(stack, ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}' || ch == '"') {
            if (stack_empty(stack)) 
            {
                stack_delete(stack);
                return "NO";
            }

            char top = stack_get(stack);
            stack_pop(stack);

            if (top != pairs[ch]) 
            {
                stack_delete(stack);
                return "NO";
            }
        }
    }

    if (stack_empty(stack)) {
        stack_delete(stack);
        return "YES";
    } else {
        stack_delete(stack);
        return "NO";
    }
}

int main() {
    std::string input;
    std::ifstream input_file("input.txt");

    if (input_file.is_open()) {
        std::getline(input_file, input);
        input_file.close();  
    } else {
        std::cerr << "Не удалось открыть файл input.txt. Введите данные вручную:\n";
        std::getline(std::cin, input);
    }

    std::cout << check_balance(input) << std::endl;

    return 0;
}
