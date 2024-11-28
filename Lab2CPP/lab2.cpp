#include <iostream>
#include <fstream>
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        return 1;
    }
    Stack *stack = stack_create();
    string commands;

    getline(input, commands);

    execute_befunge(stack, commands);
    stack_delete(stack);
    input.close();
    return 0;
}