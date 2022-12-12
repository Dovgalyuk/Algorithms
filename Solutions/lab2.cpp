//
// Created by Artem Raykh on 06.12.2022.
//

#include <iostream>
#include "list.h"
#include "stack.h"
#include <string>

int calculate(Stack *stack, const char &operation) {

    int firstValue = stack_get(stack);
    stack_pop(stack);
    int secondValue = stack_get(stack);
    stack_pop(stack);

    switch (operation) {
        case '+': return  secondValue + firstValue;
        case '-': return secondValue - firstValue;
        case '*': return secondValue * firstValue;
        case '/': return secondValue / firstValue;
    }

    return -1;
}

bool isOperation(const char &ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

Stack *parseFrom(const std::string& input) {
    Stack *stack = stack_create();

    int result, currentNumber = 0;

    for(auto ch: input) {

        if (isdigit(ch)) {
            currentNumber = 10 * currentNumber + ch - '0';

        } else if (ch) {

            if (ch == '\n')
                break;

            if (currentNumber) {
                stack_push(stack, currentNumber);
                currentNumber = NULL;
            }

            if (ch != ' ' && isOperation(ch)) {
                result = calculate(stack, ch);
                stack_push(stack, result);
            }
        }
    }
    if (currentNumber) {
        stack_push(stack, currentNumber);
    }

    std::cout << "Final result: " << result << std::endl;

    return stack;
}

int main() {

    std::string input;

    std::cout << "Enter an expression: " << std::endl;
    std::getline(std::cin, input);

    Stack *stack = parseFrom(input);

    stack_delete(stack);
}

