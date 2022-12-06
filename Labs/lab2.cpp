#include "vector.h"
#include "stack.h"
#include <iostream>
#include "conio.h"
#include <fstream>
using namespace std;

bool balanced(const std::string& s, Stack* stack)
{
    
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

void test(const string s, Stack* stack) {
    fstream file("path.txt", fstream::in | fstream::out | fstream::app);

    if (file.is_open()) {
        if (balanced(s, stack)) file << '"' << s << '"' << " : Yes\n";
        else file << '"' << s << '"' << " : No\n";
    }
    file << "-----------------\n";

    file.close();
}
int main()
{
    string message;
    Stack* stack = stack_create();
    cout << "press the 'esc' to finish\nOr press other buttons to continue\n";
    while (_getch() != 27) {
        cout << "input message: ";
        cin >> message;
        test(message, stack);
        cout << "press the 'esc' to finish\nOr press other buttons to continue\n";
    }
    stack_delete(stack);
    return 0;
}


