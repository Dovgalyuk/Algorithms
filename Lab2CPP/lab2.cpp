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

string task(string &input) {
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

    if (isSuccess && stack.empty())
        return "YES";
    else
        return "NO";
}

int main(int argc, char **argv) {

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    string line;
    string result;

    while (getline(inputFile, line)) {
        result = task(line);
        cout << result << endl;
        outputFile << result << endl;
    }

    return 0;
}