#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

// Проверяем, является ли символ кавычкой (обычной или типографской)
bool is_quote(unsigned char c) {
    // В UTF-8 типографские кавычки занимают несколько байт,
    // поэтому мы ловим их начальные байты (0xE2) или обычные ASCII.
    return c == '"' || c == '\'' || c == 0xE2;
}

// Для типографских кавычек возвращаем тип: 1 - двойная, 2 - одинарная
// Для обычных кавычек просто считаем их.
int main(int argc, char** argv) {
    if (argc < 2) return 1;

    std::ifstream input(argv[1]);
    if (!input.is_open()) return 1;

    std::string line;
    if (std::getline(input, line)) {
        Stack* stack = stack_create();
        bool valid = true;

        for (size_t i = 0; i < line.length(); ++i) {
            unsigned char c = line[i];

            // Обработка скобок
            if (c == '(' || c == '[' || c == '{') {
                stack_push(stack, (Data)c);
            }
            else if (c == ')' || c == ']' || c == '}') {
                if (stack_empty(stack)) {
                    valid = false; break;
                }
                char top = (char)stack_get(stack);
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    valid = false; break;
                }
                stack_pop(stack);
            }
            // Обработка кавычек (игнорируем байты UTF-8, ловим только первую часть)
            else if (c == '"' || c == '\'') {
                // Если на верхушке такая же кавычка — закрываем, иначе открываем
                if (!stack_empty(stack) && (char)stack_get(stack) == c) {
                    stack_pop(stack);
                } else {
                    stack_push(stack, (Data)c);
                }
            }
            else if (c == 0xE2) {
                // Это начало UTF-8 символов “ ” ‘ ’.
                // Просто пропускаем следующие 2 байта, чтобы не сломать логику скобок.
                // Но так как нам нужно проверять парность, мы будем считать ВСЕ типографские кавычки
                // просто как один тип "кавычка".
                // Чтобы определить, открывающая она или закрывающая, посмотрим на стек:
                // мы будем хранить в стеке специальный маркер для типографских кавычек.
                if (!stack_empty(stack) && (char)stack_get(stack) == 'Q') {
                    stack_pop(stack);
                } else {
                    stack_push(stack, (Data)'Q');
                }
                i += 2; // пропускаем 2 байта UTF-8
            }
        }

        if (!stack_empty(stack)) valid = false;
        stack_delete(stack);

        std::cout << (valid ? "YES" : "NO") << "\n";
    }
    return 0;
}