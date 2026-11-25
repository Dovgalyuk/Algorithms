#include "assembler.h"
#include <iostream>
#include <cctype>

char *readExpression(FILE *input) {
    std::string expression;
    int element;

    while ((element = fgetc(input)) != EOF && element != '\n') {
        expression += static_cast<char>(element);
    }

    char *ptr = new char[expression.size() + 1];
    std::copy(expression.begin(), expression.end(), ptr);
    ptr[expression.size()] = '\0';
    return ptr;
}

bool checkEnd(const char *element) {
    return *element == '\0';
}

static int priority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

static void applyTopOperator(Stack *ops, Stack *values) {
    char op = static_cast<char>(stack_get(ops));
    stack_pop(ops);

    switch (op) {
        case '+': addionFunction(values);        break;
        case '-': subtractionFunction(values);   break;
        case '*': multiplicationFunction(values); break;
        default: break;
    }
}

void parseExpression(const char *p, Stack *stack) {
    Stack *ops = stack_create();

    while (*p != '\0') {
        char c = *p;

        if (c == ' ' || c == '\t') { p++; continue; }

        if (std::isdigit(static_cast<unsigned char>(c))) {
            stackPush(c - '0', stack);
            p++;
        } else if (c == '(') {
            stack_push(ops, static_cast<Data>('('));
            p++;
        } else if (c == ')') {
            while (!stack_empty(ops) && static_cast<char>(stack_get(ops)) != '(') {
                applyTopOperator(ops, stack);
            }
            if (!stack_empty(ops)) {
                stack_pop(ops);
            }
            p++;
        } else if (c == '+' || c == '-' || c == '*') {
            while (!stack_empty(ops) &&
                   static_cast<char>(stack_get(ops)) != '(' &&
                   priority(static_cast<char>(stack_get(ops))) >= priority(c)) {
                applyTopOperator(ops, stack);
            }
            stack_push(ops, static_cast<Data>(c));
            p++;
        } else {
            p++;
        }
    }

    while (!stack_empty(ops)) {
        applyTopOperator(ops, stack);
    }

    stack_delete(ops);
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;

    char *expression = readExpression(input);
    fclose(input);

    if (checkEnd(expression)) {
        delete[] expression;
        return 1;
    }

    Stack *stack = stack_create();

    parseExpression(expression, stack);

    stack_delete(stack);
    delete[] expression;

    return 0;
}