#include "stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

void process_expression(const string& expr) {
    Stack* stack = stack_create(); 
    Stack* operators = stack_create(); 
    stringstream output;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        if (isdigit(c)) {
            output << "PUSH " << c << "\n";
            stack_push(stack, c - '0'); 
        } else if (c == '(') {
            stack_push(operators, c); 
        } else if (c == ')') {
            while (!stack_empty(operators) && stack_get(operators) != '(') {
                char op = stack_get(operators);
                stack_pop(operators);

                int b = stack_get(stack); stack_pop(stack);
                int a = stack_get(stack); stack_pop(stack);

                if (op == '+') {
                    output << "POP A\nPOP B\nADD A, B\nPUSH A\n";
                    stack_push(stack, a + b);
                } else if (op == '-') {
                    output << "POP A\nPOP B\nSUB A, B\nPUSH A\n";
                    stack_push(stack, a - b);
                } else if (op == '*') {
                    output << "POP A\nPOP B\nMUL A, B\nPUSH A\n";
                    stack_push(stack, a * b);
                }
            }
            if (!stack_empty(operators) && stack_get(operators) == '(') {
                stack_pop(operators);  
            }
        } else if (c == '+' || c == '-') {
            while (!stack_empty(operators) && (stack_get(operators) == '*' || stack_get(operators) == '/')) {
                char op = stack_get(operators);
                stack_pop(operators);

                int b = stack_get(stack); stack_pop(stack);
                int a = stack_get(stack); stack_pop(stack);

                if (op == '+') {
                    output << "POP A\nPOP B\nADD A, B\nPUSH A\n";
                    stack_push(stack, a + b);
                } else if (op == '-') {
                    output << "POP A\nPOP B\nSUB A, B\nPUSH A\n";
                    stack_push(stack, a - b);
                }
            }
            stack_push(operators, c);
        } else if (c == '*' || c == '/') {
            stack_push(operators, c);
        }
    }

    while (!stack_empty(operators)) {
        char op = stack_get(operators);
        stack_pop(operators);

        int b = stack_get(stack); stack_pop(stack);
        int a = stack_get(stack); stack_pop(stack);

        if (op == '+') {
            output << "POP A\nPOP B\nADD A, B\nPUSH A\n";
            stack_push(stack, a + b);
        } else if (op == '-') {
            output << "POP A\nPOP B\nSUB A, B\nPUSH A\n";
            stack_push(stack, a - b);
        } else if (op == '*') {
            output << "POP A\nPOP B\nMUL A, B\nPUSH A\n";
            stack_push(stack, a * b);
        }
    }

    cout << output.str();
    stack_delete(stack);
    stack_delete(operators);
}

int main() {
    string expr;
    cin >> expr;
    process_expression(expr);
    return 0;
}
