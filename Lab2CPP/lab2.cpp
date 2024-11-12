#include <iostream>
#include <fstream>
#include <string>
#include <cwchar>
#include "stack.h"
bool isMatchingPair(wchar_t opening, wchar_t closing) {
    return (opening == L'(' && closing == L')') ||
           (opening == L'[' && closing == L']') ||
           (opening == L'{' && closing == L'}') ||
           (opening == L'\u201C' && closing == L'\u201D') ||
           (opening == L'\u2018' && closing == L'\u2019');
}



bool isValidSequence(const std::string& sequence) {
    Stack *stack = stack_create(); // Создаём стек
    for (wchar_t ch : sequence) {
        if (ch == L'(' || ch == L'[' || ch == L'{' || ch == L'\u201C' || ch == L'\u201D') {
            stack_push(stack, static_cast<Data>(ch)); // Передаем корректный тип данных
        } else if (ch == L')' || ch == L']' || ch == L'}' || ch == L'\u2018' || ch == L'\u2019') {
            if (stack_empty(stack)) {
                stack_delete(stack); // Освобождаем память перед выходом
                return false; // Неправильная последовательность
            }

            wchar_t data = stack_get(stack);
            stack_pop(stack);
            if (!isMatchingPair(data, ch)) { // Разыменовываем указатель
                stack_delete(stack); // Освобождаем память перед выходом
                return false; // Неправильная последовательность
            }
        }
    }

    bool result = stack_empty(stack); // Проверяем, пуст ли стек
    stack_delete(stack); // Освобождаем память
    return result; // Если стек пуст, последовательность правильная
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
