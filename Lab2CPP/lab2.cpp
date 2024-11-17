#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
bool isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}') ||
           (opening == '"' && closing == '"') ||
           (opening == '\'' && closing == '\'');
}

bool isValidSequence(const std::string& sequence) {
    Stack *stack = stack_create(); // Создаем стек
    for (char ch : sequence) {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '"' || ch == '\'') {
            if (!stack_empty(stack)) {
                if (stack_get(stack) == '"' || stack_get(stack) == '\'') {
                    char opening = stack_get(stack);
                    if (!isMatchingPair(opening, ch)) {
                        stack_delete(stack);
                        return false;
                    }
                    stack_pop(stack);
                }
            }
            stack_push(stack, static_cast<Data>(ch));
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack_empty(stack)) {
                stack_delete(stack);
                return false;
            }
            char opening = stack_get(stack);
            if (!isMatchingPair(opening, ch)) {
                stack_delete(stack);
                return false;
            }
            
            stack_pop(stack);
        }
    }

    // Проверяем, пуст ли стек и закрыты ли кавычки
    bool result = stack_empty(stack); 
    stack_delete(stack); // Освобождаем память
    return result; // Если стек пуст и кавычки закрыты, последовательность правильная
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string sequence;
    std::getline(input, sequence); // Считываем строку из файла

    if (isValidSequence(sequence)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    input.close(); // Закрываем файл
    return 0;
}
