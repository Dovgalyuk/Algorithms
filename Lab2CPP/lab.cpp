#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

bool check_brackets_and_quotes(const std::string& str) {
    Stack* stack = stack_create();

    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];

        if (c == '(') {
            // Открывающая скобка - всегда помещаем в стек
            stack_push(stack, c);
        }
        else if (c == ')') {
            // Закрывающая скобка - проверяем соответствие
            if (stack_empty(stack) || stack_get(stack) != '(') {
                stack_delete(stack);
                return false;
            }
            stack_pop(stack);
        }
        else if (c == '\"' || c == '\'') {
            // Для кавычек проверяем, есть ли такая же кавычка на вершине стека
            if (!stack_empty(stack) && stack_get(stack) == c) {
                // Нашли закрывающую кавычку - удаляем открывающую
                stack_pop(stack);
            }
            else {
                // Открывающая кавычка - помещаем в стек
                stack_push(stack, c);
            }
        }
    }

    // Если стек пуст - все скобки и кавычки сбалансированы
    bool result = stack_empty(stack);
    stack_delete(stack);
    return result;
}

int main(int argc, char* argv[]) {
    std::string filename = "input.txt";

    if (argc >= 2) {
        filename = argv[1];
    }

    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cout << "Error: Cannot open file " << filename << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(input_file, line)) {
        if (check_brackets_and_quotes(line)) {
            std::cout << "YES" << std::endl;
        }
        else {
            std::cout << "NO" << std::endl;
        }
    }

    input_file.close();
    return 0;
}
