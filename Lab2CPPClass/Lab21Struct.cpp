#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <stdexcept>
#include "stack.h"

using namespace std;

void processScript(Stack& stack, const string& script, const string& input) {
    size_t inputIndex = 0;
    for (char cmd : script) {
        switch (cmd) {
        case '+': {
            string str;
            size_t pos = script.find('+', inputIndex);
            if (pos == string::npos) {
                str = script.substr(inputIndex);
                inputIndex = script.length();
            }
            else {
                str = script.substr(inputIndex, pos - inputIndex);
                inputIndex = pos + 1;
            }
            for (char c : str) {
                stack.push(c);
            }
            break;
        }
        case '-': {
            if (!stack.empty()) {
                stack.pop();
            }
            break;
        }
        case '<': {
            if (!stack.empty()) {
                char top = stack.get();
                stack.pop();
                Stack temp;
                while (!stack.empty()) {
                    temp.push(stack.get());
                    stack.pop();
                }
                stack.push(top);
                while (!temp.empty()) {
                    stack.push(temp.get());
                    temp.pop();
                }
            }
            break;
        }
        case '>': {
            if (!stack.empty()) {
                Stack temp;
                while (!stack.empty()) {
                    temp.push(stack.get());
                    stack.pop();
                }
                char bottom = temp.get();
                temp.pop();
                while (!temp.empty()) {
                    stack.push(temp.get());
                    temp.pop();
                }
                stack.push(bottom);
            }
            break;
        }
        case '?': {
            if (inputIndex < input.length()) {
                stack.push(input[inputIndex]);
                inputIndex++;
            }
            break;
        }
        case '!': {
            if (!stack.empty()) {
                cout << (char)stack.get() << endl;
            }
            break;
        }
        default:
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <script_file> <input_file>" << endl;
        return 1;
    }

    string scriptFile = argv[1];
    string inputFile = argv[2];

    ifstream scriptStream(scriptFile);
    if (!scriptStream) {
        cerr << "Cannot open script file: " << scriptFile << endl;
        return 1;
    }
    string script((istreambuf_iterator<char>(scriptStream)), istreambuf_iterator<char>());
    scriptStream.close();

    ifstream inputStream(inputFile);
    if (!inputStream) {
        cerr << "Cannot open input file: " << inputFile << endl;
        return 1;
    }
    string input((istreambuf_iterator<char>(inputStream)), istreambuf_iterator<char>());
    inputStream.close();

    Stack stack;
    try {
        processScript(stack, script, input);

        Stack temp;
        while (!stack.empty()) {
            temp.push(stack.get());
            stack.pop();
        }
        while (!temp.empty()) {
            cout << (char)temp.get() << endl;
            temp.pop();
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

}