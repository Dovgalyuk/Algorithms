#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

void execute_befunge(Stack *stack, string commands) {
    // TODO: implement befunge interpreter
    for (char cmd : commands){
        if (cmd >= '0' && cmd <= '9'){
            stack_push(stack, cmd - '0');
        } else {
            switch (cmd){
                case '+': {
                    Data b = stack_get(stack);
                    stack_pop(stack);
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a + b);
                    break;
                }
                case '-': {
                    Data b = stack_get(stack);
                    stack_pop(stack);
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a - b);
                    break;
                }
                case '*': {
                    Data b = stack_get(stack);
                    stack_pop(stack);
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, a * b);
                    break;
                }
                case '/': {
                    Data b = stack_get(stack);
                    stack_pop(stack);
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    if (b != 0) {
                        stack_push(stack, a / b);
                    } else {
                        cerr << "Division by zero" << endl;
                        stack_push(stack, 0);
                    }
                    break;
                }
                case '%': {
                    Data b = stack_get(stack);
                    stack_pop(stack);
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    if (b != 0) {
                        stack_push(stack, a % b);
                    } else {
                        cerr << "Division by zero" << endl;
                        stack_push(stack, 0);
                    }
                    break;
                }
                case '!': {
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    if (a == 0) {
                        stack_push(stack, 1);
                    } else {
                        stack_push(stack, 0);
                    }
                    break;
                }
                case '`': {
                    Data b = stack_get(stack);
                    stack_pop(stack);
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    if (a < b) {
                        stack_push(stack, 1);
                    } else {
                        stack_push(stack, 0);
                    }
                    break;
                }
                case ':': {
                    Data a = stack_get(stack);
                    stack_push(stack, a);
                    break;
                }
                case '.': {
                    Data a = stack_get(stack);
                    stack_pop(stack);
                    cout << (char)a;
                    break;
                }
                case '&' : {
                    Data input;
                    cout << "Enter input: ";
                    cin >> input;
                    stack_push(stack, input);
                    break;
                }
                default: {
                    cerr << "Invalid command: " << cmd << endl;
                    break;
                }
            }
        }
    }
}

int main() {
    Stack *stack = stack_create();
    string commands;

    cout << "Enter commands: ";
    cin >> commands;

    execute_befunge(stack, commands);
    stack_delete(stack);
    // FILE *input = fopen("input.txt", "r");
    // if (!input) {
    //     return 1;
    // }
    // stack = stack_create_and_read(input);
    
    return 0;
}