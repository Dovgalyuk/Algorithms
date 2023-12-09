#include <iostream>
#include <sstream>
#include <vector>
#include "stack.h"

#include "list.h"

using namespace std;

bool evaluateExpression(const vector<string>& expression) {
    Stack* stack = stack_create();

    for (const string& token : expression) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            stack_push(stack, stod(token)); 
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack_empty(stack)) {
                cout << "UNDERFLOW" << endl;
                stack_delete(stack);
                return false;
            }

            double operand2 = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack)) {
                cout << "UNDERFLOW" << endl;
                stack_delete(stack);
                return false;
            }

            double operand1 = stack_get(stack);
            stack_pop(stack);

            if (token == "/" && operand2 == 0) {
                cout << "ZERO" << endl;
                stack_delete(stack);
                return false;
            }

            if (token == "+") {
                stack_push(stack, operand1 + operand2);
            }
            else if (token == "-") {
                stack_push(stack, operand1 - operand2);
            }
            else if (token == "*") {
                stack_push(stack, operand1 * operand2);
            }
            else if (token == "/") {
                stack_push(stack, operand1 / operand2);
            }
        }
    }

    if (!stack_empty(stack)) {
        cout << "OVERFLOW" << endl;
        stack_delete(stack);
        return false;
    }

    stack_delete(stack);
    return true;
}

int main() {
    vector<string> expression1 = { "1", "2", "+", "3" };
    vector<string> expression2 = { "10", "9", "-", "+" };

    if (evaluateExpression(expression1)) {
        cout << "OK" << endl;
    }

    if (evaluateExpression(expression2)) {
        cout << "OK" << endl;
    }

    return 0;
}