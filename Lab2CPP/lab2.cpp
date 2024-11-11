#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "list.h"
#include "stack.h"

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infix_to_rpn(const string& expression) {
    Stack* operators = stack_create();
    stringstream output;

    for (size_t i = 0; i < expression.size(); ++i) {
        char token = expression[i];

        if (isspace(token)) {
            continue;
        }
        if (isdigit(token)) {
            while (i < expression.size() && isdigit(expression[i])) {
                output << expression[i++];
            }
            output << ' ';
            --i;
        }
        else if (token == '(') {
            stack_push(operators, token);
        }
        else if (token == ')') {
            while (!stack_empty(operators) && static_cast<char>(stack_get(operators)) != '(') {
                output << static_cast<char>(stack_get(operators)) << ' ';
                stack_pop(operators);
            }
            stack_pop(operators);
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/') {
            while (!stack_empty(operators) && precedence(static_cast<char>(stack_get(operators))) >= precedence(token)) {
                output << static_cast<char>(stack_get(operators)) << ' ';
                stack_pop(operators);
            }
            stack_push(operators, token);
        }
    }

    while (!stack_empty(operators)) {
        output << static_cast<char>(stack_get(operators)) << ' ';
        stack_pop(operators);
    }

    stack_delete(operators);
    return output.str();
}

void generate_stack_instructions(const string& rpn_expression) {
    stringstream tokens(rpn_expression);
    string token;

    while (tokens >> token) {
        if (isdigit(token[0])) {
            int temp_value = stoi(token);
            cout << "PUSH " << temp_value << endl;
        } else {
            cout << "POP A" << endl;
            cout << "POP B" << endl;

            if (token[0] == '+') {
                cout << "ADD A, B" << endl;
            } else if (token[0] == '-') {
                cout << "SUB A, B" << endl;
            } else if (token[0] == '*') {
                cout << "MUL A, B" << endl;
            }

            cout << "PUSH A" << endl;
        }
    }
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

    while (getline(input, expression)) {
        string rpn_expression = infix_to_rpn(expression);

        generate_stack_instructions(rpn_expression);
    }

    input.close();
    return 0;
}
