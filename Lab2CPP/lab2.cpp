#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

using namespace std;

// Функция для определения приоритета операций
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для преобразования инфиксного выражения в постфиксное
string infixToPostfix(istream* input) { // (1+2)*3 -> 12+3*
    string expression;
    getline(*input, expression);

    Stack* operators = stack_create();
    string postfix;

    for (char ch : expression) {
        if (isdigit(ch)) {
            postfix += ch; // Добавляем цифру в постфиксное выражение
        }
        else if (ch == '(') {
            stack_push(operators, ch); // Помещаем '(' в стек
        }
        else if (ch == ')') {
            while (!stack_empty(operators) && stack_get(operators) != '(') {
                postfix += static_cast<char>(stack_get(operators));
                stack_pop(operators);
            }
            stack_pop(operators); // Удаляем '(' из стека
        }
        else {
            while (!stack_empty(operators) && getPrecedence(static_cast<char>(stack_get(operators))) >= getPrecedence(ch)) {
                postfix += static_cast<char>(stack_get(operators));
                stack_pop(operators);
            }
            stack_push(operators, ch); // Помещаем оператор в стек
        }
    }

    while (!stack_empty(operators)) {
        postfix += static_cast<char>(stack_get(operators));
        stack_pop(operators);
    }

    stack_delete(operators); 
    return postfix;
}

// Функция для генерации ассемблерных команд из постфиксного выражения
void generateAssembly(const string& postfix) {
    Stack* stack = stack_create();

    for (char ch : postfix) {
        if (isdigit(ch)) {
            cout << "PUSH " << ch << endl;
            stack_push(stack, ch - '0'); // Преобразуем символ в число и помещаем в стек
        }
        else {
            cout << "POP A" << endl;
            int a = stack_get(stack);
            stack_pop(stack);

            cout << "POP B" << endl;
            int b = stack_get(stack);
            stack_pop(stack);

            if (ch == '+') {
                cout << "ADD A, B" << endl;
                stack_push(stack, a + b);
            }
            else if (ch == '*') {
                cout << "MUL A, B" << endl;
                stack_push(stack, a * b);
            }
            else if (ch == '-') {
                cout << "SUB A, B" << endl;
                stack_push(stack, b - a);
            }

            cout << "PUSH A" << endl;
        }
    }

    stack_delete(stack); // Удаляем стек
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    istream* input = &cin;
    ifstream inputFile;

    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    string postfix = infixToPostfix(input); // Преобразуем инфиксное выражение в постфиксное
    generateAssembly(postfix); // Генерируем ассемблерные команды

    return 0;
}