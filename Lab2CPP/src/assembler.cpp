#include "assembler.h"
#include <iostream>

char *readExpression(FILE *input) {
    std::string expression = "";
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

const char *parseFactor(const char *p, Stack *stack) {
    while (*p == ' ') p++;

    if (*p == '(') {
        p = parseExpr(p + 1, stack);
        return p + 1;
    }

    stackPush(*p - '0', stack);
    return p + 1;
}

const char *parseTerm(const char *p, Stack *stack) {
    p = parseFactor(p, stack);
    while (*p == '*') {
        p = parseFactor(p + 1, stack);
        multiplicationFunction(stack);
    }
    return p;
}

const char *parseExpr(const char *p, Stack *stack) {
    p = parseTerm(p, stack);
    while (*p == '+' || *p == '-') {
        char op = *p;
        p = parseTerm(p + 1, stack);
        if (op == '+') addionFunction(stack);
        else subtractionFunction(stack);
    }
    return p;
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

    parseExpr(expression, stack);

    stack_delete(stack);
    delete[] expression;

    return 0;
}