#include "stack.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <stack>
using namespace std;


void process_expression(const string& expr) {
    Stack* stack = stack_create();
    stringstream output;

    stack<char> operators;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        if (isdigit(c)) {
            output << "PUSH " << c << "\n";
            stack_push(stack, c - '0');
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();

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
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        } else if (c == '+' || c == '-') {
            while (!operators.empty() && (operators.top() == '*' || operators.top() == '/')) {
                char op = operators.top();
                operators.pop();

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
            operators.push(c);
        } else if (c == '*' || c == '/') {
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

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
}

int main() {
    string expr;
    cin >> expr;
    process_expression(expr);
    return 0;
}