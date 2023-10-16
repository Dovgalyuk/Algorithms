#include <iostream>
#include <string>
#include "stack.h"

using namespace std;
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int applyOperation(int a, int b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b != 0) {
            return a / b;
        }
        else {
            cerr << "Error: Division by zero" << endl;
            exit(1);
        }
    }
    return 0;
}

int evaluateExpression(const string& expression) {
    Stack* operands = stack_create();
    Stack* operators = stack_create();

    size_t index = 0;
    while (index < expression.length()) {
        char c = expression[index];

        if (c == ' ') {
            index++;
            continue;
        }

        if (isdigit(c)) {
            int operand = 0;
            while (index < expression.length() && isdigit(expression[index])) {
                operand = operand * 10 + (expression[index] - '0');
                index++;
            }
            stack_push(operands, operand);
        }
        else if (c == '(') {
            stack_push(operators, c);
            index++;
        }
        else if (c == ')') {
            while (!stack_empty(operators) && stack_get(operators) != '(') {
                int b = stack_get(operands);
                stack_pop(operands);
                int a = stack_get(operands);
                stack_pop(operands);
                char op = (char)stack_get(operators);
                stack_pop(operators);
                int result = applyOperation(a, b, op);
                stack_push(operands, result);
            }
            stack_pop(operators);
            index++;
        }
        else {
            while (!stack_empty(operators) &&
                precedence(c) <= precedence((char)stack_get(operators))) {
                int b = stack_get(operands);
                stack_pop(operands);
                int a = stack_get(operands);
                stack_pop(operands);
                char op = (char)stack_get(operators);
                stack_pop(operators);
                int result = applyOperation(a, b, op);
                stack_push(operands, result);
            }
            stack_push(operators, c);
            index++;
        }
    }

    while (!stack_empty(operators)) {
        int b = stack_get(operands);
        stack_pop(operands);
        int a = stack_get(operands);
        stack_pop(operands);
        char op = (char)stack_get(operators);
        stack_pop(operators);
        int result = applyOperation(a, b, op);
        stack_push(operands, result);
    }

    int finalResult = stack_get(operands);
    stack_delete(operands);
    stack_delete(operators);
    return finalResult;
}

int main() {
    setlocale(LC_ALL, "RUS");
    string expression;
    cout << "Введите арифметическое выражение: ";
    getline(cin, expression);

    int result = evaluateExpression(expression);
    cout << "Результат: " << result << endl;

    return 0;
}