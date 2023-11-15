#include <iostream>
#include <string>
#include "stack.h"  
using namespace std;

// Функция для проверки, является ли символ оператором
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*';
}

// Функция для получения ассемблерной операции по оператору
string getOperation(char op) {
    if (op == '+') {
        return "ADD";
    }
    else if (op == '-') {
        return "SUB";
    }
    else if (op == '*') {
        return "MUL";
    }    
    else {
        return "";  // По умолчанию возвращаем пустую строку
    }
}

// Функция для получения приоритета оператора
int getPriority(char op) {
    if (op == '(') {
        return 3; // Приоритет скобок установлен выше
    }
    else if (op == '*') {
        return 2;
    }
    else if (op == '+' || op == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

// Функция для преобразования арифметического выражения в ассемблерный код
void convertToAssembly(const string& expression) {
    Stack* stack = stack_create();  // Создание стека для хранения операторов

    for (char c : expression) {
        if (isdigit(c)) {
            cout << "PUSH " << c << endl;  // Вывод инструкции для сохранения числа в стек
        }
        else if (isOperator(c)) {
            while (!stack_empty(stack) && getPriority(stack_get(stack)) >= getPriority(c)) {                
                stack_pop(stack);  // Выталкивание операторов с более высоким приоритетом
            }
            stack_push(stack, c);  // Добавление текущего оператора в стек
        }
        else if (c == '(') {
            stack_push(stack, c);  // Добавление открывающей скобки в стек
        }
        else if (c == ')') {
            while (!stack_empty(stack) && stack_get(stack) != '(') {
                cout << "POP A\n";
                cout << "POP B\n";
                cout << getOperation(stack_get(stack)) << " A, B\n";  // Генерация кода для операции
                cout << "PUSH A\n";
                stack_pop(stack);  // Выталкивание оператора из стека
            }
            if (!stack_empty(stack) && stack_get(stack) == '(') {
                stack_pop(stack);  // Удаление открывающей скобки из стека
            }
        }
    }

    while (!stack_empty(stack)) {
        cout << "POP A\n";
        cout << "POP B\n";
        cout << getOperation(stack_get(stack)) << " A, B\n";  // Генерация кода для операции
        cout << "PUSH A\n";
        stack_pop(stack);  // Выталкивание оператора из стека
    }

    stack_delete(stack);  // Освобождение памяти, выделенной для стека
}

int main() {
    string expression;
    cout << "Enter the arithmetic expression: ";
    getline(cin, expression);  // Ввод арифметического выражения

    cout << "Converting to assembly:" << endl;
    convertToAssembly(expression);  // Вызов функции преобразования в ассемблерный код

    return 0;
}
