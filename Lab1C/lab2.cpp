#include "stack.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
    Stack stack;
    int a = 0, b = 0, c = 0, d = 0;

    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    string line;
    int addres = -1;
    bool error = false;
    while (getline(input_file, line) && !error) {
        istringstream iss(line);
        string command, number = " ";

        iss >> command;
        iss >> number;

        if (command == "push") {
            if (stoi(number) == -1) {
                cout << "BAD PUSH\n";
                error = true;
                break;
            }
            stack.push(stoi(number));
        }

        if (command == "pop") {
            if (stack.get() == -1) {
                cout << "BAD POP\n";
                error = true;
                break;
            } else {
                if (number == "A") {
                    a = stack.get();
                    stack.pop();
                }
                if (number == "B") {
                    b = stack.get();
                    stack.pop();
                }
                if (number == "C") {
                    c = stack.get();
                    stack.pop();
                }
                if (number == "D") {
                    d = stack.get();
                    stack.pop();
                }
            }
        }

        if (command == "call") {
            stack.push(addres);
        }

        if (command == "ret") {
            if (stack.get() != -1) {
                cout << "BAD RET\n";
                error = true;
                break;
            } else {
                stack.pop();
            }
        }

        if (command == "add") {
            int value = stack.get();
            stack.pop();
            if (value < 0 || stack.get() < 0) {
                cout << "BAD ADD\n";
                error == true;
                break;
            }
            value += stack.get();
            stack.pop();
            stack.push(value);
        }

        if (command == "sub") {
            int value = stack.get();
            stack.pop();
            if (value < 0 || stack.get() < 0) {
                cout << "BAD SUB\n";
                error == true;
                break;
            }
            value -= stack.get();
            if (value < 0) {
                value = 0;
            }
            stack.pop();
            stack.push(value);
        }

        if (command == "mul") {
            int value = stack.get();
            stack.pop();
            if (value < 0 || stack.get() < 0) {
                cout << "BAD MUL\n";
                error == true;
                break;
            }
            value *= stack.get();
            stack.pop();
            stack.push(value);
        }
    }

    if (!error) {
        cout << "A = " << a << endl
             << "B = " << b << endl
             << "C = " << c << endl
             << "D = " << d << endl;
    }

    input_file.close();
    return 0;
}
