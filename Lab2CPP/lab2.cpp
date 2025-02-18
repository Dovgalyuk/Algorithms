#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "../LibraryCPP/stack.h"

// Возвращение приоритета оператора
int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

// Проверка на символ оператора
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Преобразование инфиксного выражения в постфиксное
std::string convertInfixToPostfix(const std::string& expression) {
    Stack* stack = stack_create();
    std::string output;

    for (char c : expression) {
        if(std::isspace(static_cast<unsigned char>(c))) continue;
        if(std::isalnum(static_cast<unsigned char>(c))) {
            // Если операнд, сразу добавляем его в выходную строку
            output.push_back(c);
        }
        else if (c == '(') {
            stack_push(stack, c);
        }
        else if (c == ')') {
            // Извлечение операторов до открывающей скобки
            while(!stack_empty(stack) && static_cast<char>(stack_get(stack)) != '(') {
                output.push_back(static_cast<char>(stack_get(stack)));
                stack_pop(stack);
            }
            if(stack_empty(stack)) {
                stack_delete(stack);
                throw std::runtime_error("Ошибка: несбалансированные скобки.");
            }
            stack_pop(stack); // Удаление открывающей скобки
        }
        else if (isOperator(c)) {
            // Извлечение из стека операторы с большим или равным приоритетом
            while(!stack_empty(stack) && isOperator(static_cast<char>(stack_get(stack))) &&
                  precedence(static_cast<char>(stack_get(stack))) >= precedence(c)) {
                output.push_back(static_cast<char>(stack_get(stack)));
                stack_pop(stack);
            }
            stack_push(stack, c);
        }
        else {
            stack_delete(stack);
            throw std::runtime_error(std::string("Ошибка: неизвестный символ '") + c + "'.");
        }
    }

    // Извлечение оставшихся операторов из стека
    while(!stack_empty(stack)) {
        if(static_cast<char>(stack_get(stack)) == '(') {
            stack_delete(stack);
            throw std::runtime_error("Ошибка: несбалансированные скобки.");
        }
        output.push_back(static_cast<char>(stack_get(stack)));
        stack_pop(stack);
    }

    stack_delete(stack);
    return output;
}

// Чтение выражения из файла
std::string readExpression(int argc, char* argv[]) {
    std::istream* input = &std::cin;
    std::ifstream inputFile;
    std::string expression;

    if(argc >= 2) {
        inputFile.open(argv[1]);
        if(!inputFile) {
            throw std::runtime_error("Ошибка: файл не найден: " + std::string(argv[1]));
        }
        input = &inputFile;
    }

    std::getline(*input, expression);
    if(expression.empty()){
        std::string fileName = (argc >= 2 ? std::string(argv[1]) : "");
        throw std::runtime_error("Ошибка: выражение не может быть пустым." + fileName);
    }
    return expression;
}

int main(int argc, char* argv[]) {
    try {
        std::string expression = readExpression(argc, argv);
        std::string postfix = convertInfixToPostfix(expression);
        std::cout << "Постфиксная форма: " << postfix << std::endl;
        return 0;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
