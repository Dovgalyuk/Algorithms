#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "stack.h"

using namespace std;

void processScript(Stack& stack, const string& script, const string& input) {
    size_t inputIndex = 0;

    for (size_t i = 0; i < script.length(); i++) {
        char cmd = script[i];

        switch (cmd) {
        case '+': {
            i++; 
            string str;
            while (i < script.length()) {
                char c = script[i];
                if (c == '+' || c == '-' || c == '<' || c == '>' || c == '?' || c == '!') {
                    i--;
                    break;
                }
                str += c;
                i++;
            }
            for (int j = str.length() - 1; j >= 0; j--) {
                stack.push(str[j]);
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
        case '.': {
            if (!stack.empty()) {
                char top = stack.get();
                stack.push(top);
            }
            break;
        }
        case '@': {
            if (stack.empty()) break;
            char top1 = stack.get();
            stack.pop();
            if (stack.empty()) {
                stack.push(top1);
                break;
            }
            char top2 = stack.get();
            stack.pop();
            stack.push(top1);
            stack.push(top2);
            break;
        }
        case '~': {
            Stack temp;
            while (!stack.empty()) {
                temp.push(stack.get());
                stack.pop();
            }
            stack = temp;
            break;
        }
        case '^': {
            if (!stack.empty()) {
                stack.pop();
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
    string script;
    getline(scriptStream, script);
    scriptStream.close();

    ifstream inputStream(inputFile);
    if (!inputStream) {
        cerr << "Cannot open input file: " << inputFile << endl;
        return 1;
    }
    string input;
    getline(inputStream, input);
    inputStream.close();

    Stack stack;
    try {
        processScript(stack, script, input);

        if (!stack.empty()) {
            cout << (char)stack.get() << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

}