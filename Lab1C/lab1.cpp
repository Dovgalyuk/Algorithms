#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isOpening(char c) { return c == '(' || c == '"' || c == '\''; }
bool isClosing(char c) { return c == ')' || c == '"' || c == '\''; }

bool isMatching(char open, char close)
{
    if (open == '(' && close == ')') return true;
    if (open == '"' && close == '"') return true;
    if (open == '\'' && close == '\'') return true;
    return false;
}

bool checkString(const string& s)
{
    Stack* stack = stack_create();
    bool ok = true;

    for (char c : s) {
        if (isOpening(c)) {
            stack_push(stack, (Data)c);
        } else if (isClosing(c)) {
            if (stack_empty(stack)) { ok = false; break; }
            char top = (char)stack_get(stack);
            if (!isMatching(top, c)) { ok = false; break; }
            stack_pop(stack);
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