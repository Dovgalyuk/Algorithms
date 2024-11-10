#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "list.h"
#include "stack.h"

using namespace std;

// Функция для определения приоритета операторов
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для преобразования инфиксной нотации в обратную польскую нотацию (RPN)
string infix_to_rpn(const string& expression) {
    Stack* operators = stack_create();
    stringstream output;

    for (size_t i = 0; i < expression.size(); ++i) {
        char token = expression[i];

        // Пропуск пробелов
        if (isspace(token)) {
            continue;
        }
        // Если символ - цифра, добавляем его в выходной поток
        if (isdigit(token)) {
            while (i < expression.size() && isdigit(expression[i])) {
                output << expression[i++];
            }
            output << ' ';
            --i;
        }
        // Если открывающая скобка, помещаем в стек
        else if (token == '(') {
            stack_push(operators, token);
        }
        // Если закрывающая скобка, выталкиваем из стека до открывающей скобки
        else if (token == ')') {
            while (!stack_empty(operators) && static_cast<char>(stack_get(operators)) != '(') {
                output << static_cast<char>(stack_get(operators)) << ' ';
                stack_pop(operators);
            }
            stack_pop(operators); // Убираем открывающую скобку
        }
        // Если оператор, обрабатываем приоритеты
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!stack_empty(operators) && precedence(static_cast<char>(stack_get(operators))) >= precedence(token)) {
                output << static_cast<char>(stack_get(operators)) << ' ';
                stack_pop(operators);
            }
            stack_push(operators, token);
        }
    }

    // Выталкиваем оставшиеся операторы из стека
    while (!stack_empty(operators)) {
        output << static_cast<char>(stack_get(operators)) << ' ';
        stack_pop(operators);
    }

    stack_delete(operators);
    return output.str();
}

// Функция для генерации ассемблерных команд на основе RPN выражения
void generate_stack_instructions(const string& rpn_expression) {
    Stack* values = stack_create();
    stringstream tokens(rpn_expression);
    string token;
    int temp_value = 0; // Инициализируем temp_value, чтобы избежать предупреждений компилятора

    while (tokens >> token) {
        // Если токен - число, помещаем его в стек
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            temp_value = stoi(token);
            cout << "PUSH " << temp_value << endl;
            stack_push(values, temp_value);
        } else {
            cout << "POP A" << endl;
            stack_pop(values);
            cout << "POP B" << endl;
            stack_pop(values);

            // Выполняем операцию в зависимости от оператора
            if (token[0] == '+') {
                cout << "ADD A, B" << endl;
            } else if (token[0] == '-') {
                cout << "SUB A, B" << endl;
            } else if (token[0] == '*') {
                cout << "MUL A, B" << endl;
            }

            cout << "PUSH A" << endl;
            stack_push(values, temp_value);
        }
    }

    stack_delete(values);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Ошибка открытия файла" << endl;
        return 1;
    }

    string expression;

    // Чтение каждой строки из входного файла
    while (getline(input, expression)) {
        // Преобразуем входное выражение в RPN
        string rpn_expression = infix_to_rpn(expression);

        // Генерируем ассемблерные инструкции
        generate_stack_instructions(rpn_expression);
    }

    input.close();
    return 0;
}
