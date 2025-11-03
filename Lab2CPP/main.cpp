#include "stack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string input_filename = (argc > 1) ? argv[1] : "input.txt";
    ifstream input(input_filename);
    if (!input.is_open()) {
        cerr << "Cannot open " << input_filename << endl;
        return 1;
    }

    string line;
    if (!getline(input, line)) {
        cerr << "Empty input file" << endl;
        return 1;
    }

    istringstream iss(line);
    Stack* stk = stack_create();
    string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack_empty(stk) || stack_empty(stk)) {  // Проверка на недостаток элементов
                cerr << "Invalid expression" << endl;
                stack_delete(stk);
                return 1;
            }
            Data b = stack_get(stk); stack_pop(stk);
            Data a = stack_get(stk); stack_pop(stk);
            Data res = 0;  // Инициализация для устранения предупреждения
            if (token == "+") res = a + b;
            else if (token == "-") res = a - b;
            else if (token == "*") res = a * b;
            else if (token == "/") res = a / b;
            stack_push(stk, res);
        } else {
            try {
                Data num = stoi(token);
                stack_push(stk, num);
            } catch (...) {
                cerr << "Invalid number: " << token << endl;
                stack_delete(stk);
                return 1;
            }
        }
    }

    if (stack_empty(stk)) {
        cerr << "Empty expression" << endl;
    } else {
        cout << stack_get(stk) << endl;
    }

    stack_delete(stk);
    return 0;
}