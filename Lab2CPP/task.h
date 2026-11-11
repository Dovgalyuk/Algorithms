#ifndef ALGORITHMS_TASK_H
#define ALGORITHMS_TASK_H
#include <string>
#include "stack.h"

enum OperatorCode {
    UNKNOWN = 0,
    PLUS = -1,
    MINUS = -2,
    MUL = -3,
    LEFT_PAR = -4,
    RIGHT_PAR = -5,
};


int getPriority(char op);

void convertToRPN(const std::string& str, Stack *stack);

void generateAssembler(Stack *rnpStack, std::ofstream& out);

#endif
