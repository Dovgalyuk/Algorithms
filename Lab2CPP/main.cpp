#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include "stack.h"

// Токены: число или оператор/скобка
struct Token {
    bool is_num{};
    int value{};   // если число: значение; если оператор: char в int ('+','-','*','(',')')
};

static int prec(int op) {
    if (op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Без <filesystem>: пытаемся открыть аргумент как файл, иначе — трактуем как выражение
static bool read_input_expr(int argc, char** argv, std::string& out) {
    if (argc > 1) {
        std::string arg = argv[1];

        // Попробуем как файл
        std::ifstream in(arg);
        if (in.good()) {
            std::getline(in, out);
            return true;
        }
        // Иначе это выражение
        out = arg;
        return true;
    }
    else {
        return static_cast<bool>(std::getline(std::cin, out));
    }
}

int main(int argc, char** argv) {
    std::string s;
    if (!read_input_expr(argc, argv, s)) return 0;

    // 1) Лексер
    std::vector<Token> infix;
    for (size_t i = 0; i < s.size();) {
        unsigned char ch = static_cast<unsigned char>(s[i]);
        if (std::isspace(ch)) { ++i; continue; }
        if (std::isdigit(ch)) {
            int val = 0;
            while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) {
                val = val * 10 + (s[i] - '0');
                ++i;
            }
            infix.push_back(Token{ true, val });
        }
        else {
            char c = s[i++];
            if (c == '+' || c == '-' || c == '*' || c == '(' || c == ')') {
                infix.push_back(Token{ false, static_cast<int>(c) });
            }
            else {
                std::cerr << "Unexpected character: " << c << "\n";
                return 1;
            }
        }
    }

    // 2) Шунтирующий алгоритм -> RPN (используем стек из LibraryCPP)
    std::vector<Token> rpn;
    Stack* op = stack_create(); // стек операторов

    for (const auto& t : infix) {
        if (t.is_num) {
            rpn.push_back(t);
        }
        else {
            char c = static_cast<char>(t.value);
            if (c == '(') {
                stack_push(op, static_cast<int>('('));
            }
            else if (c == ')') {
                while (!stack_empty(op) && stack_get(op) != static_cast<int>('(')) {
                    rpn.push_back(Token{ false, stack_get(op) });
                    stack_pop(op);
                }
                if (!stack_empty(op) && stack_get(op) == static_cast<int>('(')) {
                    stack_pop(op); // remove '('
                }
                else {
                    std::cerr << "Mismatched parentheses\n";
                    stack_delete(op);
                    return 1;
                }
            }
            else { // + - *
                int cur = static_cast<int>(c);
                while (!stack_empty(op)) {
                    int top = stack_get(op);
                    if (top == static_cast<int>('(')) break;
                    if (prec(top) >= prec(cur)) {
                        rpn.push_back(Token{ false, top });
                        stack_pop(op);
                    }
                    else break;
                }
                stack_push(op, cur);
            }
        }
    }
    while (!stack_empty(op)) {
        int top = stack_get(op);
        if (top == static_cast<int>('(')) { std::cerr << "Mismatched parentheses\n"; stack_delete(op); return 1; }
        rpn.push_back(Token{ false, top });
        stack_pop(op);
    }
    stack_delete(op);

    // 3) Генерация «asm»-команд по RPN
    // Число:  PUSH n
    // Оператор: POP A; POP B; <OP> A, B; PUSH A
    for (const auto& t : rpn) {
        if (t.is_num) {
            std::cout << "PUSH " << t.value << "\n";
        }
        else {
            char c = static_cast<char>(t.value);
            std::cout << "POP A\n";
            std::cout << "POP B\n";
            if (c == '+') std::cout << "ADD A, B\n";
            else if (c == '-') std::cout << "SUB A, B\n";
            else if (c == '*') std::cout << "MUL A, B\n";
            else { std::cerr << "Unknown operator in RPN\n"; return 1; }
            std::cout << "PUSH A\n";
        }
    }
    return 0;
}
