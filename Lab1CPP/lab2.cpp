#include <iostream>
#include <stack>
#include "list.h"
#include "stack.h"
using namespace std;

int main()
{
    int numbers; const char* expression = "";
    cout << "Select expression: \n1. 1+2*3 \n2. (1+2)*3\n\n";
    cin >> numbers;
    if (numbers == 1) {
        expression = "1+2*3";
    }
    else if (numbers == 2) {
        expression = "(1+2)*3";
    }
    cout << endl;

    stack<char> opstack;

    List* list = list_create();
    Stack* stack = stack_create();

    for (char c = *expression; c != 0; c = *expression++) {
        switch (c) {
        case '+':
        case '-':
        case '*':
            opstack.push(c);
            break;
        case '(':
            opstack.push(c);
            break;
        case ')':
            while (!opstack.empty() && opstack.top() != '(') {
                int rhs = stack_get(stack); cout << "POP A\n";  stack_pop(stack);
                int lhs = stack_get(stack); cout << "POP B\n";  stack_pop(stack);
                char op = opstack.top(); opstack.pop();
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
            opstack.pop(); // remove '(' from opStack
            break;
        default:
            int number = (c - '0'); cout << "PUSH " << number << endl;
            stack_push(stack, number);
            break;
        }
    }

    while (!opstack.empty() && opstack.top() != '(') {
        int rhs = stack_get(stack); cout << "POP A\n"; stack_pop(stack);
        int lhs = stack_get(stack); cout << "POP B\n"; stack_pop(stack);
        char op = opstack.top(); opstack.pop();
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

    while (!opstack.empty())
    {
        opstack.pop();
    }

    stack_delete(stack);
    list_delete(list);

    return 0;
}
