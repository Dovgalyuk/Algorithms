#include <iostream>
#include <stack>
#include "list.h"
#include "stack.h"
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*')
        return 2;
    return 0;
}

int main()
{
    string strexpression; const char* charexpression = "";
    cout << "Enter an expression: \n\n";
    cin >> strexpression; charexpression = strexpression.c_str();

    List* oplist = list_create();
    Stack* opstack = stack_create();

    List* list = list_create();
    Stack* stack = stack_create();

    for (char c = *charexpression; c != 0; c = *charexpression++) {
        switch (c) {
        case '+':
        case '-':
        case '*':
            while (stack_empty(opstack) == false && precedence(stack_get(opstack)) >= precedence(c)) {
                int rhs = stack_get(stack); std::cout << "POP A\n"; stack_pop(stack);
                int lhs = stack_get(stack); std::cout << "POP B\n"; stack_pop(stack);
                char op = stack_get(opstack); stack_pop(opstack);
                switch (op) {
                case '+':
                    stack_push(stack, lhs + rhs); std::cout << "ADD A, B\nPUSH A\n";
                    break;
                case '-':
                    stack_push(stack, lhs - rhs); std::cout << "SUB A, B\nPUSH A\n";
                    break;
                case '*':
                    stack_push(stack, lhs * rhs); std::cout << "MUL A, B\nPUSH A\n";
                    break;
                }
            }
            stack_push(opstack, c);
            break;
        case '(':
            stack_push(opstack, c);
            break;
        case ')':
            while (stack_empty(opstack) == false && stack_get(opstack) != '(') {
                int rhs = stack_get(stack); cout << "POP A\n";  stack_pop(stack);
                int lhs = stack_get(stack); cout << "POP B\n";  stack_pop(stack);
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
            stack_pop(opstack); // remove '(' from opStack
            break;
        default:
            int number = (c - '0'); cout << "PUSH " << number << endl;
            stack_push(stack, number);
            break;
        }
    }

    while (stack_empty(opstack) == false && stack_get(opstack) != '(') {
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

    int final_result = stack_get(stack);
    std::cout << "\nResult = " << final_result << std::endl;

    while (stack_empty(opstack) == false)
    {
        stack_pop(opstack);
    }

    stack_delete(stack);
    list_delete(list);

    return 0;
}
