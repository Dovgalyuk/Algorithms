#include <iostream>
#include <string>
#include <fstream>
#include "stack.h"
#include "task.h"


int main() {
    std::string expr;

    std::getline(std::cin, expr);

    Stack *stack = stack_create();
    convertToRPN(expr, stack);

    std::ofstream output("output.txt");
    if (output.is_open()) {
        generateAssembler(stack, output);
        output.close();
    }

    stack_delete(stack);
    return 0;
}
