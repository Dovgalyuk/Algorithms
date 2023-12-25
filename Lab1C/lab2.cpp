#include <iostream>
#include "list.h"
#include "stack.h"

using namespace std;

int main() {
    Stack* stack = stack_create();

    char command;
    int operand;

    while (cin >> command) {
        if (isdigit(command)) {
            operand = command - '0';
            stack_push(stack, operand);
        } else if (command == '+') {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a + b);
                }
            }
        } else if (command == '-') {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a - b);
                }
            }
        } else if (command == '*') {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a * b);
                }
            }
        } else if (command == '/') {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (b != 0 && !stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a / b);
                }
            }
        } else if (command == '%') {
            if (!stack_empty(stack)) {
                int b = stack_get(stack);
                stack_pop(stack);
                if (b != 0 && !stack_empty(stack)) {
                    int a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a % b);
                }
            }
        } else if (command == 'd' && cin >> command && command == 'u' && cin >> command && command == 'p') {
            if (!stack_empty(stack)) {
                int top = stack_get(stack);
                stack_push(stack, top);
            }
        } else if (command == 'd' && cin >> command && command == 'r' && cin >> command && command == 'o' && cin >> command && command == 'p') {
            stack_pop(stack);
        } else if (command == 's' && cin >> command && command == 'w' && cin >> command && command == 'a' && cin >> command && command == 'p') {
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
        } else if (command == 'o' && cin >> command && command == 'v' && cin >> command && command == 'e' && cin >> command && command == 'r') {
            if (!stack_empty(stack)) {
                int top = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int second = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, second);
                    stack_push(stack, top);
                    stack_push(stack, second);
                }
            }
        } else if (command == 'r' && cin >> command && command == 'o' && cin >> command && command == 't') {
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
        } else if (command == '.') {
            if (!stack_empty(stack)) {
                cout << stack_get(stack) << endl;
                stack_pop(stack);
            }
        } else {
            // Неизвестная команда
        }
    }

    stack_delete(stack);
    return 0;
}
