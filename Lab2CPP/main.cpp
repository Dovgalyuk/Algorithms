#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include "stack.h"

using namespace std;

void convertToStackOperations(const string& expression) {
    Stack* opStack = stack_create();

    for (char c : expression) {
        if (isdigit(c)) {
            cout << "PUSH " << c << endl;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack_empty(opStack)) {
                char topOp = static_cast<char>(stack_get(opStack));
                if ((c == '+' || c == '-') && (topOp == '*' || topOp == '/')) {
                    stack_pop(opStack);
                    
                    cout << "POP A" << endl;
                    cout << "POP B" << endl;
                    cout << (topOp == '+' ? "ADD" : topOp == '-' ? "SUB" : topOp == '*' ? "MUL" : "DIV") << " A, B" << endl;
                    cout << "PUSH A" << endl;
                } else {
                    break;
                }
            }
            stack_push(opStack, c);
        } else if (c == '(') {
            stack_push(opStack, c);
        } else if (c == ')') {
            while (!stack_empty(opStack) && static_cast<char>(stack_get(opStack)) != '(') {
                char op = static_cast<char>(stack_get(opStack));
                stack_pop(opStack);
                
                cout << "POP A" << endl;
                cout << "POP B" << endl;
                cout << (op == '+' ? "ADD" : op == '-' ? "SUB" : op == '*' ? "MUL" : "DIV") << " A, B" << endl;
                cout << "PUSH A" << endl;
            }
            stack_pop(opStack);
        }
    }

    while (!stack_empty(opStack)) {
        char op = static_cast<char>(stack_get(opStack));
        stack_pop(opStack);
        
        cout << "POP A" << endl;
        cout << "POP B" << endl;
        cout << (op == '+' ? "ADD" : op == '-' ? "SUB" : op == '*' ? "MUL" : "DIV") << " A, B" << endl;
        cout << "PUSH A" << endl;
    }

    stack_delete(opStack);
}

int main(int argc, char* argv[]) {
    istream* input = &cin;
    ifstream inputFile;

    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Ошибка: не удалось открыть файл " << argv[1] << endl;
            return 1;
        }
        input = &inputFile;
    }

    string expression;
    while (getline(*input, expression)) {
        convertToStackOperations(expression);
        cout << "---" << endl;
    }

    return 0;
}
