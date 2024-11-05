#include "befunge_interpreter.h"
#include <iostream>
#include <stdexcept>
#include <cctype>

Interpreter::Interpreter() : stack_() {}

void Interpreter::run(const std::string &program) {
    for (char command : program) {
        execute(command);
    }
}

void Interpreter::execute(char command) {
    if (isdigit(command)) {
        stack_.push(command - '0');
    } else {
        switch (command) {
            case '+': performBinaryOp([](int a, int b) { return a + b; }); break;
            case '-': performBinaryOp([](int a, int b) { return a - b; }); break;
            case '*': performBinaryOp([](int a, int b) { return a * b; }); break;
            case '/': performBinaryOp([](int a, int b) { 
                if (b == 0) throw std::runtime_error("Division by zero");
                return a / b; 
            }); break;
            case '%': performBinaryOp([](int a, int b) { 
                if (b == 0) throw std::runtime_error("Modulo by zero");
                return a % b; 
            }); break;
            case '!': {
                int value = pop();
                stack_.push(value == 0 ? 1 : 0);
                break;
            }
            case '`': {
                int b = pop();
                int a = pop();
                stack_.push(a > b ? 1 : 0);
                break;
            }
            case ':': {
                int value = getTop();
                stack_.push(value);
                break;
            }
            case '.': {
                int value = pop();
                std::cout << value << std::endl;
                break;
            }
            case '&': {
                int input;
                std::cout << "Enter a number: ";
                std::cin >> input;
                stack_.push(input);
                break;
            }
            default:
                throw std::runtime_error("Unknown command");
        }
    }
}

int Interpreter::pop() {
    if (stack_.empty()) throw std::runtime_error("Stack underflow");
    int value = stack_.get();
    stack_.pop();
    return value;
}

int Interpreter::getTop() const {
    if (stack_.empty()) throw std::runtime_error("Stack is empty");
    return stack_.get();
}

void Interpreter::performBinaryOp(const std::function<int(int, int)>& operation) {
    int b = pop();
    int a = pop();
    stack_.push(operation(a, b));
}
