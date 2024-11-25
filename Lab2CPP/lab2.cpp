#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

using namespace std;

int precedence(size_t op) {
    if (op == '+') return 1;
    if (op == '*') return 2;
    return 0; 
}

void performOperation(size_t op, ofstream& output) {
    output << "POP B" << endl; 
    output << "POP A" << endl; 

    if (op == '+') {
        output << "ADD A, B" << endl;
    } else if (op == '*') {
        output << "MUL A, B" << endl;
    }

    output << "PUSH A" << endl; 
}

void translateToAssembly(const string& expr, ofstream& output) {
    Stack* stack = stack_create();
    
    for (size_t i = 0; i < expr.size(); ++i) {
        char token = expr[i];

        if (isspace(token)) {
            continue; 
        }

        if (isdigit(token)) {
            int value = 0;
            while (i < expr.size() && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                ++i;
            }
            --i;
            output << "PUSH " << value << endl; 
        } 
        else if (token == '(') {
            stack_push(stack, token); 
        } 
        else if (token == ')') {
            while (!stack_empty(stack) && stack_get(stack) != '(') {
                size_t op = stack_get(stack); 
                performOperation(op, output);
                stack_pop(stack); 
            }
            stack_pop(stack); 
        } 
        else if (token == '+' || token == '*') {
            while (!stack_empty(stack) && precedence(stack_get(stack)) >= precedence(token)) {
                size_t op = stack_get(stack); 
                performOperation(op, output);
                stack_pop(stack); 
            }
            stack_push(stack, token); 
        }
    }

    while (!stack_empty(stack)) {
        size_t op = stack_get(stack);
        performOperation(op, output);
        stack_pop(stack);
    }

    stack_delete(stack); 
}

int main() {
    string expression;
    cout << "Enter the arithmetic expression: ";
    getline(std::cin, expression);
    
    ofstream output("output.txt"); 
    translateToAssembly(expression, output); 

    output.close(); 
    return 0;
}