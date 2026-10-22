#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
using namespace std;

bool Check(ifstream &file) {
    Stack stack;
    char symbol;
    while (file >> symbol) {
        if (symbol == '(' || symbol == '[' || symbol == '{') {
            stack.push(symbol);
        }
        else if (symbol == ')') {
            if (stack.empty() || stack.get() != '(') {
                return false;
            }
            stack.pop();
        }
        else if (symbol == ']') {
            if (stack.empty() || stack.get() != '[') {
                return false;
            }
            stack.pop();
        }
        else if (symbol == '}') {
            if (stack.empty() || stack.get() != '{') {
                return false;
            }
            stack.pop();
        }
    }
    return stack.empty();
}

int main(int argc, char* argv[]) {
    string filename = "input1.txt";
    if (argc >= 2) {
        filename = argv[1];
    }
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "файл не найден";
        return 1;
    }

    if (Check(file)) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }

    file.close();
    return 0;
}
