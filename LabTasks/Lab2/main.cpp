#include <iostream>
#include <string>
#include "stack.h"
#include "Interpreter.hpp"

Interpreter::Interpreter() {
    stack = stack_create();
}
void Interpreter::setString(const std::string str) {
    this->str = str;
}
void Interpreter::run() {
    for(char chr : str) {
        if(chr >= '0' && chr <= '9') {
            int val = static_cast<int>(chr)-48;
            stack_push(stack, val);
            continue;
        } 
        if (chr == '&') {
            int number;
            std::cout << "Input a number:" << std::endl;

            while(!(std::cin >> number) || (number < 0) || (number > 9)) {
                std::cout << "Error: incorrect values!" << std::endl;
                std::cout << "Input a number:" << std::endl;
                std::cin.clear();
                std::cin.ignore();
            }
            continue;
        }
        if(!stack_empty(stack)) {
            switch (chr) {
                case ':': {
                    int val = stack_get(stack);
                    stack_push(stack, val);
                    break;
                }
                case '.':
                    std::cout << stack_get(stack) << std::endl;
                    stack_pop(stack);
                    break;
                case '`': {
                    int val_1 = stack_get(stack);
                    stack_pop(stack);
                    int val_2 = stack_get(stack); 
                    stack_pop(stack);

                    if(val_1 > val_2) {
                        stack_push(stack, 1);
                    } else {
                        stack_push(stack, 0);
                    }
                    break;
                }
                case '!': {
                    int val = stack_get(stack);
                    stack_pop(stack);

                    if (val == 0) {
                        stack_push(stack, 1);
                    } else {
                        stack_push(stack, 0);
                    }
                    break;
                }
                case '+': {
                    int val_1 = stack_get(stack);
                    stack_pop(stack);
                    int val_2 = stack_get(stack);
                    stack_pop(stack);

                    int result = val_1 + val_2;
                    stack_push(stack, result);
                    break;
                }
                case '-': {
                    int val_1 = stack_get(stack);
                    stack_pop(stack);
                    int val_2 = stack_get(stack);
                    stack_pop(stack);

                    int result = val_1 - val_2;
                    stack_push(stack, result);
                    break;
                }
                case '*': {
                    int val_1 = stack_get(stack);
                    stack_pop(stack);
                    int val_2 = stack_get(stack);
                    stack_pop(stack);

                    int result = val_1 * val_2;
                    stack_push(stack, result);
                    break;
                }
                case '/': {
                    int val_1 = stack_get(stack);
                    stack_pop(stack);
                    int val_2 = stack_get(stack);
                    stack_pop(stack);

                    int result = val_1 / val_2;
                    stack_push(stack, result);
                    break;
                }
                case '%': {
                    int val_1 = stack_get(stack);
                    stack_pop(stack);
                    int val_2 = stack_get(stack);
                    stack_pop(stack);

                    int result = val_1 % val_2;
                    stack_push(stack, result);
                    break;
                }
            }
        } else {
            throw "Error: stack is empty!";
        }
    }
}
Interpreter::~Interpreter () {
    stack_delete(stack);
}

int main() {
    Interpreter *interpreter = new Interpreter;

    std::string str_input;
    std::cout << "Input str:" << std::endl;
    std::getline(std::cin, str_input); 

    interpreter->setString(str_input);
    try {
        interpreter->run();
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }

    delete interpreter;
}