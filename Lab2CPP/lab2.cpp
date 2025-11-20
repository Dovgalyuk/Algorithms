#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

using namespace std;

bool isPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}') ||
           (open == '<' && close == '>');
}

bool isOpening(char c) {
    return c == '(' || c == '[' || c == '{' || c == '<';
}

void task(string &input) {
    Stack<char> stack;
    bool isSuccess = true;

    for (size_t i = 0; i < input.length(); i++) {
        char current = input[i];

        if (isOpening(current))
            stack.push(current);
        else {
            if (stack.empty()) {
                isSuccess = false;
                break;
            }

            char top = stack.get();

            if (isPair(top, current))
                stack.pop();
            else {
                isSuccess = false;
                break;
            }
        }
    }

    if (isSuccess && stack.empty()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main(int argc, char **argv) {

    ifstream inputFile(argv[1]);

    string line;
    getline(inputFile, line);

    task(line);

    return 0;
}