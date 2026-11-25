#include "operations.h"
#include "stack.h"
#include <iostream>

void stackPush(const int &value, Stack *stack) {
    stack_push(stack, value);
    std::cout << "PUSH " << value << std::endl;
}

int stackPop(const char letter, Stack *stack) {
    int value = stack_get(stack);
    std::cout << "POP " << letter << std::endl;
    stack_pop(stack);
    return value;
}

void addionFunction(Stack *stack) {
    int a = stackPop('A', stack);
    int b = stackPop('B', stack);

    std::cout << "ADD A, B" << std::endl;

    stack_push(stack, a + b);
    std::cout << "PUSH A" << std::endl;
}

void subtractionFunction(Stack *stack) {
    int a = stackPop('A', stack);
    int b = stackPop('B', stack);

    std::cout << "SUB B, A" << std::endl;

    stack_push(stack, b - a);
    std::cout << "PUSH B" << std::endl;
}

void multiplicationFunction(Stack *stack) {
    int a = stackPop('A', stack);
    int b = stackPop('B', stack);

    std::cout << "MUL A, B" << std::endl;

    stack_push(stack, a * b);
    std::cout << "PUSH A" << std::endl;
}