#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

bool check_brackets(const string &s) {
    Stack *stack = stack_create();
    bool correct = true;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];

        if (c == '(') {
            stack_push(stack, (Data)c);
        } else if (c == ')') {
            if (stack_empty(stack) || (char)stack_get(stack) != '(') {
                correct = false;
                break;
            }
            stack_pop(stack);
        } else if (c == '\'' || c == '\"') {
            if (!stack_empty(stack) && (char)stack_get(stack) == c) {
                stack_pop(stack);
            } else {
                stack_push(stack, (Data)c);
            }
        }
    }

    if (!stack_empty(stack)) {
        correct = false;
    }

    stack_delete(stack);
    return correct;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        return 1;
    }

    string text;
    getline(file, text);
    file.close();

    if (check_brackets(text)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}