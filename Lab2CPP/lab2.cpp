#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "stack.h"

#define ADD_SUB 1
#define MUL_DIV 2
#define ZERO 0

using namespace std;

int precedence(char op);
string polish(const string& line);

int main(int argc, char *argv[]) {
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file! " << endl;
        return EXIT_FAILURE;
    }

    string line_from_file;
    getline(input, line_from_file);
    input.close();

    cout << polish(line_from_file) << endl;

    return 0;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return ADD_SUB;
        case '*':
        case '/':
            return MUL_DIV;
        default:
            return ZERO;
    }
}

string polish(const string& line) {
    Stack *stack = stack_create();
    string output;

    for (char ch : line) {
        if (isalnum(ch)) {
            output += ch;
        }
        else if (ch == '(') {
            stack_push(stack, ch);
        }
        else if (ch == ')') {
            while (!stack_empty(stack) && stack_get(stack) != '(') {
                output += stack_get(stack);
                stack_pop(stack);
            }
            if (!stack_empty(stack)) {
                stack_pop(stack); // Удаляем (
            }
        }
        else {
            while (!stack_empty(stack) && precedence(stack_get(stack)) >= precedence(ch)) {
                output += stack_get(stack);
                stack_pop(stack);
            }
            stack_push(stack, ch);
        }
    }

    while (!stack_empty(stack)) {
        output += stack_get(stack);
        stack_pop(stack);
    }

    stack_delete(stack);

    return output;
}
