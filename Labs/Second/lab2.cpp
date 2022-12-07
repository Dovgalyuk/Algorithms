#include <iostream>
#include <regex>
#include <fstream>
#include "stack.h"

using namespace std;

static const string PUSH_COMMAND = "PUSH ";
static const string POP_COMMAND = "POP ";

bool isNumber(const string &str) {
    static const regex r(R"([0-9]+)");
    return regex_match(str.data(), r);
}

int main() {
    Stack *stack = stack_create();

    int A = 0, B = 0, C = 0, D = 0;
    string str;

    ifstream file(R"(D:\CLion\Labs\Second\test.txt)");

    if (file.is_open()) {
        while (getline(file, str)) {
            if (!str.find(PUSH_COMMAND)) {
                string streamStr = str.substr(5);
                if (isNumber(streamStr))
                    stack_push(stack, stoi(streamStr));
                else {
                    switch (str[PUSH_COMMAND.size()]) {
                        case 'A': {
                            stack_push(stack, A);
                            break;
                        }
                        case 'B': {
                            stack_push(stack, B);
                            break;
                        }
                        case 'C': {
                            stack_push(stack, C);
                            break;
                        }
                        case 'D': {
                            stack_push(stack, D);
                            break;
                        }
                        default: {
                            cout << "ERROR: not recognize -> " << str << endl;
                            file.close();
                            break;
                        }
                    }
                }
            } else if (!str.find(POP_COMMAND)) {
                switch (str[POP_COMMAND.size()]) {
                    case 'A': {
                        A = stack_get(stack);
                        stack_pop(stack);
                        break;
                    }
                    case 'B': {
                        B = stack_get(stack);
                        stack_pop(stack);
                        break;
                    }
                    case 'C': {
                        C = stack_get(stack);
                        stack_pop(stack);
                        break;
                    }
                    case 'D': {
                        D = stack_get(stack);
                        stack_pop(stack);
                        break;
                    }
                    default: {
                        cout << "ERROR: not recognize -> " << str << endl;
                        file.close();
                        break;
                    }
                }
            } else {
                cout << "ERROR: Command recognition exception  -> " << str << endl;
                file.close();
            }
        }
        file.close();
        cout << "A = " << A << endl << "B = " << B << endl << "C = " << C << endl << "D = " << D << endl;
    } else {
        cout << "ERROR: Opening file" << endl;
    }

    stack_delete(stack);
}