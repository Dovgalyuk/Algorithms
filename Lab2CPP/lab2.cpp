#include "stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

void process_expression(const string& expr) {
    Stack* operators = stack_create();
    stringstream output;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        if (isdigit(c)) {  
            output << "PUSH " << c << "\n";
        } 
        else if (c == '(') {
            stack_push(operators, c);
        } 
        else if (c == ')') {
            while (!stack_empty(operators) && stack_get(operators) != '(') {
                char op = stack_get(operators);
                stack_pop(operators);
                
                output << "POP B\nPOP A\n";
                if (op == '+') output << "ADD A, B\n";
                if (op == '-') output << "SUB A, B\n";
                if (op == '*') output << "MUL A, B\n";
                if (op == '/') output << "DIV A, B\n";
                output << "PUSH A\n";
            }
            stack_pop(operators);
        } 
        else if (c == '+' || c == '-') {
            while (!stack_empty(operators) && (stack_get(operators) == '*' || stack_get(operators) == '/')) {
                char op = stack_get(operators);
                stack_pop(operators);

                output << "POP B\nPOP A\n";
                if (op == '*') output << "MUL A, B\n";
                if (op == '/') output << "DIV A, B\n";
                output << "PUSH A\n";
            }
            stack_push(operators, c);
        } 
        else if (c == '*' || c == '/') {
            stack_push(operators, c);
        }
    }

    while (!stack_empty(operators)) {
        char op = stack_get(operators);
        stack_pop(operators);

        output << "POP B\nPOP A\n";
        if (op == '+') output << "ADD A, B\n";
        if (op == '-') output << "SUB A, B\n";
        if (op == '*') output << "MUL A, B\n";
        if (op == '/') output << "DIV A, B\n";
        output << "PUSH A\n";
    }

    cout << output.str();

    stack_delete(operators);
}

int main() {
    string expr;
    cin >> expr;
    process_expression(expr);
    return 0;
}
