#include "stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

void process_expression(const string& expr) {
    Stack* values = stack_create();
    Stack* operators = stack_create();
    stringstream output;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        if (isdigit(c)) {  
            int num = c - '0';
            output << "PUSH " << num << "\n";
            stack_push(values, num);
        } 
        else if (c == '(') {
            stack_push(operators, c);
        } 
        else if (c == ')') {
            while (!stack_empty(operators) && stack_get(operators) != '(') {
                char op = stack_get(operators);
                stack_pop(operators);

                int b = stack_get(values); stack_pop(values);
                int a = stack_get(values); stack_pop(values);

                output << "POP B\nPOP A\n";
                if (op == '+') output << "ADD A, B\n";
                if (op == '-') output << "SUB A, B\n";
                if (op == '*') output << "MUL A, B\n";
                if (op == '/') output << "DIV A, B\n";
                output << "PUSH A\n";

                stack_push(values, (op == '+') ? (a + b) : 
                                      (op == '-') ? (a - b) : 
                                      (op == '*') ? (a * b) : 
                                                    (a / b));
            }
            stack_pop(operators);
        } 
        else if (c == '+' || c == '-') {
            while (!stack_empty(operators) && (stack_get(operators) == '*' || stack_get(operators) == '/')) {
                char op = stack_get(operators);
                stack_pop(operators);

                int b = stack_get(values); stack_pop(values);
                int a = stack_get(values); stack_pop(values);

                output << "POP B\nPOP A\n";
                if (op == '*') output << "MUL A, B\n";
                if (op == '/') output << "DIV A, B\n";
                output << "PUSH A\n";

                stack_push(values, (op == '*') ? (a * b) : (a / b));
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

        int b = stack_get(values); stack_pop(values);
        int a = stack_get(values); stack_pop(values);

        output << "POP B\nPOP A\n";
        if (op == '+') output << "ADD A, B\n";
        if (op == '-') output << "SUB A, B\n";
        if (op == '*') output << "MUL A, B\n";
        if (op == '/') output << "DIV A, B\n";
        output << "PUSH A\n";

        stack_push(values, (op == '+') ? (a + b) : (op == '-') ? (a - b) : (op == '*') ? (a * b) : (a / b));
    }

    cout << output.str();

    stack_delete(values);
    stack_delete(operators);
}

int main() {
    string expr;
    cin >> expr;
    process_expression(expr);
    return 0;
}
