#include "vector.h"
#include "stack.h"
#include <iostream>
#include "conio.h"
#include <fstream>
using namespace std;

bool balanced(const std::string& s)
{
    Stack* stack = stack_create();
    for (char c : s) {
        switch (c) {

        case '(': stack_push(stack,')') ; break;
        case '[': stack_push(stack, ']'); break;
        case '{': stack_push(stack, '}'); break;
        case '<': stack_push(stack, '>'); break;

        case ')':
        case ']':
        case '}':
        case '>':
            if (stack_empty(stack) || stack_get(stack) != c) { return false; }
            stack_pop(stack);
            break;
        default:
            break;
        }
    }
    return stack_empty(stack);
}

void test(const string s) {
    fstream file("path.txt", fstream::in | fstream::out | fstream::app);

    if (file.is_open()) {
        if (balanced(s)) file << '"' << s << '"' << " : Yes\n";
        else file << '"' << s << '"' << " : No\n";
    }
    file << "-----------------\n";

    file.close();
}
int main()
{
    string message;
    cout << "press the 'esc' to finish\nOr press other buttons to continue\n";
    while (_getch() != 27) {
        cout << "input message: ";
        cin >> message;
        test(message);
        cout << "press the 'esc' to finish\nOr press other buttons to continue\n";
    }
    return 0;
}


