#include <iostream>
#include "list.h"
#include "stack.h"

using namespace std;

int main() {
    Stack* stack = stack_create();

    char command;
    int operand;

    while (cin >> command) {
        switch (command) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                operand = command - '0';
                stack_push(stack, operand);
                break;
            case '+':
                if (!stack_empty(stack)) {
                    int b = stack_get(stack);
                    stack_pop(stack);
                    if (!stack_empty(stack)) {
                        int a = stack_get(stack);
                        stack_pop(stack);
                        stack_push(stack, a + b);
                    }
                }
                break;
            case '-':
                if (!stack_empty(stack)) {
                    int b = stack_get(stack);
                    stack_pop(stack);
                    if (!stack_empty(stack)) {
                        int a = stack_get(stack);
                        stack_pop(stack);
                        stack_push(stack, a - b);
                    }
                }
                break;
            case '*':
                if (!stack_empty(stack)) {
                    int b = stack_get(stack);
                    stack_pop(stack);
                    if (!stack_empty(stack)) {
                        int a = stack_get(stack);
                        stack_pop(stack);
                        stack_push(stack, a * b);
                    }
                }
                break;
            case '/':
                if (!stack_empty(stack)) {
                    int b = stack_get(stack);
                    stack_pop(stack);
                    if (b != 0 && !stack_empty(stack)) {
                        int a = stack_get(stack);
                        stack_pop(stack);
                        stack_push(stack, a / b);
                    }
                }
                break;
            case '%':
                if (!stack_empty(stack)) {
                    int b = stack_get(stack);
                    stack_pop(stack);
                    if (b != 0 && !stack_empty(stack)) {
                        int a = stack_get(stack);
                        stack_pop(stack);
                        stack_push(stack, a % b);
                    }
                }
                break;
            case 'dup':
                if (!stack_empty(stack)) {
                    int top = stack_get(stack);
                    stack_push(stack, top);
                }
                break;
            case 'drop':
                stack_pop(stack);
                break;
            case 'swap':
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
                break;
            case 'over':
                if (!stack_empty(stack)) {
                    int top = stack_get(stack);
                    stack_push(stack, top);
                }
                break;
            case 'rot':
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
                break;
            case '.':
                if (!stack_empty(stack)) {
                    int top = stack_get(stack);
                    cout << top << endl;
                    stack_pop(stack);
                }
                break;
            default:
                // Неизвестная команда
                break;
        }
    }

    stack_delete(stack);
    return 0;
}
