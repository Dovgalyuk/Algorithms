#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "stack.h"

using namespace std;

int priority(char x) {
    if (x == '*' or x == '/') return 2;
    if (x == '+' or x == '-') return 1;
    return 0;
}

string infixToPostfix(const string& expr) {
    Stack *st = stack_create();
    string result = "";

    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (c == ' ') continue;

        if (isalpha(c)) {
            result += c;
        }
        else if (c == '(') {
            stack_push(st, c);
        }
        else if (c == ')') {
            bool foundOpen = false;
            while (!stack_empty(st)) {
                char top = stack_get(st);
                if (top == '(') {
                    foundOpen = true;
                    stack_pop(st);
                    break;
                }
                result += top;
                stack_pop(st);
            }
            if (!foundOpen) {
                stack_delete(st);
                return "ERROR";
            }
        }
        else if (c == '+' or c == '-' or c == '*' or c == '/') {
            while (!stack_empty(st) and priority(stack_get(st)) >= priority(c)) {
                result += stack_get(st);
                stack_pop(st);
            }
            stack_push(st, c);
        }
        else {
            stack_delete(st);
            return "ERROR";
        }
    }

    while (!stack_empty(st)) {
        char top = stack_get(st);
        if (top == '(') {
            stack_delete(st);
            return "ERROR";
        }
        result += top;
        stack_pop(st);
    }

    stack_delete(st);
    return result;
}

int main(int argc, char* argv[]) {
    string input;
    if (argc > 1) {
        ifstream file(argv[1]);
        if (file.is_open()) {
            getline(file, input);
            file.close();
        } else {
            input = argv[1];
        }
    } else {
        getline(cin, input);
    }
    string output = infixToPostfix(input);

    if (output.rfind("ERROR", 0) == 0) {
        cerr << output << endl;
        return 1;
    }

    cout << output << endl;
}