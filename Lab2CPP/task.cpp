#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "stack.h"
#include "task.h"

int getPriority(OperatorCode op) {
    if (op == PLUS || op == MINUS) {
        return 1;
    }
    if (op == MUL) {
        return 2;
    }
    return 0;
}

OperatorCode encodeOperator(char op) {
    if (op == '+') {
        return PLUS;
    }
    if (op == '-') {
        return MINUS;
    }
    if (op == '*') {
        return MUL;
    }
    if (op == '(') {
        return LEFT_PAR;
    }
    if (op == ')') {
        return RIGHT_PAR;
    }

    return UNKNOWN;
}

void convertToRPN(const std::string& str, Stack *stack) {
    Stack *operators = stack_create();
    Stack *raw = stack_create();
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];

        if (isspace(c)) {
            continue;
        }

        if (isdigit(c)) {
            std::string num;
            while (i < str.length() && isdigit(str[i])) {
                num += str[i];
                i++;
            }
            i--;
            stack_push(raw, std::stoi(num));
        }
        else if (c == '(') {
            stack_push(operators, LEFT_PAR);
        } else if (c == ')') {
            while (!stack_empty(operators) && stack_get(operators) != LEFT_PAR){
                stack_push(raw, stack_get(operators));
                stack_pop(operators);
            }
            if (!stack_empty(operators)) {
                stack_pop(operators);
            }
        } else {
            while (!stack_empty(operators) && getPriority(static_cast<OperatorCode>(stack_get(operators))) >= getPriority(encodeOperator(c))) {
                stack_push(raw, stack_get(operators));
                stack_pop(operators);
            }
            stack_push(operators, encodeOperator(c));
        }
    }

    while (!stack_empty(operators)) {
        stack_push(raw, stack_get(operators));
        stack_pop(operators);
    }
    stack_delete(operators);

    while (!stack_empty(raw)) {
        stack_push(stack, stack_get(raw));
        stack_pop(raw);
    }
    stack_delete(raw);
}

void generateAssembler(Stack *rnpStack, std::ofstream& out) {
    while (!stack_empty(rnpStack)) {
        int c = stack_get(rnpStack);
        stack_pop(rnpStack);

        if (c >= 0) {
            out << "[PUSH] " << c << '\n';
        }else {
            out << "POP A" << '\n';
            out << "POP B" << '\n';

            if (c == PLUS) {
                out << "ADD A, B" << '\n';
                out << "PUSH A" << '\n';
            }
            if (c == MINUS) {
               out << "SUB B, A" << '\n';
               out << "PUSH B" << '\n';
            }
            if (c == MUL) {
               out << "MUL A, B" << '\n';
               out << "PUSH A" << '\n';
            }

        }
    }
}
