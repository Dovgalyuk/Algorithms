#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


bool checkString(const string& s)
{
    Stack* stack = stack_create();
    bool ok = true;

    for (char c : s) {
        if (c == '(') {
            stack_push(stack, (Data)c);
        } else if (c == ')') {
            if (stack_empty(stack) || (char)stack_get(stack) != '(') {
                ok = false; break;
            }
            stack_pop(stack);
        } else if (c == '"' || c == '\'') {
            if (!stack_empty(stack) && (char)stack_get(stack) == c)
                stack_pop(stack);              // закрывающая
            else
                stack_push(stack, (Data)c);    // открывающая
        }
    }

    if (ok && !stack_empty(stack)) ok = false;

    stack_delete(stack);
    return ok;
}

int main(int argc, char** argv)
{
    istream* in = &cin;
    ifstream file;

    if (argc >= 2) {
        file.open(argv[1]);
        if (!file) {
            cerr << "Cannot open file: " << argv[1] << "\n";
            return 1;
        }
        in = &file;
    }

    string s;
    while (getline(*in, s)) {
        cout << (checkString(s) ? "YES" : "NO") << "\n";
    }

    return 0;
}