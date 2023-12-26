#include <iostream>
#include <sstream>
#include <cctype>
#include "list.h"
#include "stack.h"

using namespace std;

void processCommand(Stack* stack, const string& command) {
    stringstream ss(command);
    string op;

    while (ss >> op) {
        if (op.length() == 1 && isdigit(op[0])) {
            int operand = stoi(op);
            stack_push(stack, operand);
        } else if (op == "+") {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a + b);
                }
            }
        } else if (op == "-") {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a - b);
                }
            }
        } else if (op == "*") {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a * b);
                }
            }
        } else if (op == "/") {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (b != 0 && !stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a / b);
                }
            }
        } else if (op == "%") {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (b != 0 && !stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a % b);
                }
            }
        } else if (op == "dup") {
            if (!stack_empty(stack)) {
                int top = stack_get(stack);
                stack_push(stack, top);
            }
        } else if (op == "drop") {
            if (!stack_empty(stack)) {
                stack_pop(stack);
            }
        } else if (op == "swap") {
            if (!stack_empty(stack)) {
                int a = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int b = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a);
                    stack_push(stack, b);
                }
            }
        } else if (op == "over") {
            if (!stack_empty(stack)) {
                int top = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int second = stack_get(stack);
                    stack_push(stack, second);
                    stack_push(stack, top);
                }
            }
        } else if (op == "rot") {
            if (!stack_empty(stack)) {
                int c = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int b = stack_get(stack);
                    stack_pop(stack);
                    if (!stack_empty(stack)) {
                        int a = stack_get(stack);
                        stack_pop(stack);
                        stack_push(stack, b);
                        stack_push(stack, c);
                        stack_push(stack, a);
                    }
                }
            }
        } else if (op == ".") {
            if (!stack_empty(stack)) {
                cout << stack_get(stack) << endl;
                stack_pop(stack);
            }
        } else {

        }
    }
}

int main() {
    Stack* stack = stack_create();

    string input;
    while (getline(cin, input)) {
        processCommand(stack, input);
    }

    stack_delete(stack);
    return 0;
}
