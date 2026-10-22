#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

bool check_sequence(const std::string& str) {
    Stack* stack = stack_create();
    bool valid = true;

    for (size_t i = 0; i < str.length(); ++i) {
        unsigned char c = str[i];

        // 1. Обработка открывающих скобок
        if (c == '(' || c == '[' || c == '{') {
            stack_push(stack, (Data)c);
        }
        // 2. Обработка закрывающих скобок
        else if (c == ')' || c == ']' || c == '}') {
            if (stack_empty(stack)) {
                valid = false; break;
            }
            char top = (char)stack_get(stack);
            bool matches = (c == ')' && top == '(') ||
                           (c == ']' && top == '[') ||
                           (c == '}' && top == '{');
            if (!matches) {
                valid = false; break;
            }
            stack_pop(stack);
        }
        // 3. Обработка обычных ASCII-кавычек (", ')
        else if (c == '"' || c == '\'') {
            if (!stack_empty(stack) && (char)stack_get(stack) == c) {
                stack_pop(stack); // Закрывающая
            } else {
                stack_push(stack, (Data)c); // Открывающая
            }
        }
        // 4. Обработка типографских кавычек (“”, ‘’)
        else if (c == 0xE2) {
            if (!stack_empty(stack) && (char)stack_get(stack) == 'Q') {
                stack_pop(stack); // Закрывающая
            } else {
                stack_push(stack, (Data)'Q'); // Открывающая (маркер)
            }
            i += 2; // Пропускаем оставшиеся 2 байта UTF-8
        }
    }

    if (!stack_empty(stack)) {
        valid = false;
    }

    stack_delete(stack);
    return valid;
}

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    std::string line;
    if (std::getline(input, line)) {
        bool res = check_sequence(line);
        std::cout << (res ? "YES" : "NO") << "\n";
    }
    return 0;
}