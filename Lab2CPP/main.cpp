#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include "stack.h"

using namespace std;

int priority(char op) {
    if (op == '*') return 2;
    return 1;
}

vector<string> convertToAssembly(const string& expression) {
    vector<string> assembly;
    Stack ops;
    string number;

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (isdigit(c)) {
            number += c;
        }
        else {
            if (!number.empty()) {
                assembly.push_back("PUSH " + number);
                number.clear();
            }

            if (c == '(') {
                ops.push('(');
            }
            else if (c == ')') {
                while (!ops.empty() && (char)ops.get() != '(') {
                    char op = (char)ops.get();
                    ops.pop();

                    assembly.push_back("POP A");
                    assembly.push_back("POP B");
                    if (op == '+') {
                        assembly.push_back("ADD A, B");
                    }
                    else {
                        assembly.push_back("MUL A, B");
                    }
                    assembly.push_back("PUSH A");
                }
                if (!ops.empty()) ops.pop();
            }
            else if (c == '+' || c == '*') {
                while (!ops.empty() && (char)ops.get() != '(' &&
                    priority((char)ops.get()) >= priority(c)) {
                    char op = (char)ops.get();
                    ops.pop();

                    assembly.push_back("POP A");
                    assembly.push_back("POP B");
                    if (op == '+') {
                        assembly.push_back("ADD A, B");
                    }
                    else {
                        assembly.push_back("MUL A, B");
                    }
                    assembly.push_back("PUSH A");
                }
                ops.push(c);
            }
        }
    }

    if (!number.empty()) {
        assembly.push_back("PUSH " + number);
    }

    while (!ops.empty()) {
        char op = (char)ops.get();
        ops.pop();

        assembly.push_back("POP A");
        assembly.push_back("POP B");
        if (op == '+') {
            assembly.push_back("ADD A, B");
        }
        else {
            assembly.push_back("MUL A, B");
        }
        assembly.push_back("PUSH A");
    }

    return assembly;
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) return 1;

        ifstream input(argv[1]);
        if (!input.is_open()) return 1;

        string expression;
        getline(input, expression);

        vector<string> result = convertToAssembly(expression);
        for (size_t i = 0; i < result.size(); ++i) {
            cout << result[i] << endl;
        }
    }
    catch (...) {
        return 1;
    }

    return 0;
}