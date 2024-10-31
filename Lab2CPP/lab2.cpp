#include <iostream>
#include <sstream>
#include "stack.h"
#include <string>
#include <fstream> 

using namespace std;

// Функция для обработки чисел (добавление в стек)
void handle_number(const string& token, Stack* stack) {
    int number = stoi(token); // Преобразуем строку в число
    stack_push(stack, number); // Добавляем число в стек
}

// Функция для обработки арифметических операций
bool handle_operator(char op, Stack* stack) {
    if (stack_size(stack) < 2) return false;

    int b = stack_get(stack); // Второе число
    stack_pop(stack);
    int a = stack_get(stack); // Первое число
    stack_pop(stack);

    int result = 0;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': 
            if (b == 0) return false; // Защита от деления на 0
            result = a / b; 
            break;
        case '%': result = a % b; break;
        default: return false;
    }

    stack_push(stack, result); // Результат операции возвращаем в стек
    return true;
}

// Функция для обработки команд
bool handle_command(const string& token, Stack* stack) {
    if (token == "dup") {
        if (stack_empty(stack)) return false;
        int top = stack_get(stack);
        stack_push(stack, top);
    } else if (token == "drop") {
        if (stack_empty(stack)) return false;
        stack_pop(stack);
    } else if (token == "swap") {
        if (stack_size(stack) < 2) return false;
        int first = stack_get(stack);
        stack_pop(stack);
        int second = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, first);
        stack_push(stack, second);
    } else if (token == "over") {
        if (stack_size(stack) < 2) return false;
        int first = stack_get(stack);
        stack_pop(stack);
        int second = stack_get(stack);
        stack_push(stack, second); // Положим второй элемент на вершину
        stack_push(stack, first); // Вернем первый элемент
        stack_push(stack, second); // Положим второй элемент как копию
    } else if (token == "rot") {
        if (stack_size(stack) < 3) return false;
        int first = stack_get(stack);
        stack_pop(stack);
        int second = stack_get(stack);
        stack_pop(stack);
        int third = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, second);
        stack_push(stack, first);
        stack_push(stack, third);
    } else if (token == ".") {
        if (stack_empty(stack)) return false;
        cout << stack_get(stack) << endl;
        stack_pop(stack);
    } else {
        return false;
    }
    return true;
}

// Основная функция, которая обрабатывает строку команд
void process_input(const string& input, Stack* stack) {
    istringstream iss(input);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) { // если это число
            handle_number(token, stack);
        } else if (token.length() == 1 && string("+-*/%").find(token) != string::npos) { // Оператор
            if (!handle_operator(token[0], stack)) {
                cerr << "Ошибка: некорректная операция" << endl;
                return;
            }
        } else { // Команда (dup, drop, swap, over, rot, .)
            if (!handle_command(token, stack)) {
                cerr << "Ошибка: некорректная команда" << endl;
                return;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Проверяем, передано ли имя файла в аргументах
    if (argc < 2) {
        cerr << "Ошибка: укажите имя файла с входными данными." << endl;
        return 1;
    }

    // Используем argv[1] как имя файла
    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        Stack* stack = stack_create();
        process_input(line, stack);
        stack_delete(stack);
    }

    return 0;
}
