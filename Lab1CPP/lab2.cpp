#include <iostream>
#include <stack>
#include "list.h"
#include "stack.h"
using namespace std;

int precedence(char op) {
    if (op == '+')
        return 1;
    if (op == '-')
        return 2;
    if (op == '*')
        return 3;
    return 0;
}

void opdata(Stack* stack, Stack* opstack) {
    int rhs = stack_get(stack); cout << "POP A\n"; stack_pop(stack);
    int lhs = stack_get(stack); cout << "POP B\n"; stack_pop(stack);
    char op = stack_get(opstack); stack_pop(opstack);
    switch (op) {
    case '+':
        stack_push(stack, lhs + rhs); cout << "ADD A, B\nPUSH A\n";
        break;
    case '-':
        stack_push(stack, lhs - rhs); cout << "SUB A, B\nPUSH A\n";
        break;
    case '*':
        stack_push(stack, lhs * rhs); cout << "MUL A, B\nPUSH A\n";
        break;
    }
}

int main()
{
    string strexpression; const char* charexpression = "";
    cout << "Enter an expression: \n\n";
    cin >> strexpression; charexpression = strexpression.c_str();

    Stack* opstack = stack_create();
    Stack* stack = stack_create();

    for (char c = *charexpression; c != 0; c = *charexpression++) {
        switch (c) {
        case '+':
        case '-':
        case '*':
            while (stack_empty(opstack) == false && precedence(stack_get(opstack)) >= precedence(c)) {
                opdata(stack, opstack);
            }
            stack_push(opstack, c);
            break;
        case '(':
            stack_push(opstack, c);
            break;
        case ')':
            while (stack_empty(opstack) == false && stack_get(opstack) != '(') {
                opdata(stack, opstack);
            }
            stack_pop(opstack); // remove '(' from opStack
            break;
        default:
            int number = (c - '0'); cout << "PUSH " << number << endl;
            stack_push(stack, number);
            break;
        }
    }

    while (stack_empty(opstack) == false) {
        opdata(stack, opstack);
        stack_pop(opstack);
    }

    int result = stack_get(stack);
    cout << "\nResult = " << result << endl;

    while (stack_empty(opstack) == false && stack_empty(stack) == false)
    {
        stack_pop(stack);
        stack_pop(opstack);
    }

    stack_delete(opstack);
    stack_delete(stack);

    return 0;
}
