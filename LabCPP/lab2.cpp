#include <iostream>
#include "stack.h"
#include <sstream>

using namespace std;



int main() {
    Stack* stk = stack_create();

    string input;
    getline(cin, input);
    istringstream iss(input);
    string operation;

    while (iss >> operation) {
        if (operation == "+") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            stack_push(stk, a + b);
        }
        else if (operation == "-") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            stack_push(stk, a - b);
        }
        else if (operation == "*") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            stack_push(stk, a * b);
        }
        else if (operation == "/") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            if (a != 0) {
                stack_push(stk, b / a);
            }
            else {
                cout << "Error" << endl;
                return 1;
            }
        }
        else if (operation == "%") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            if (a != 0) {
                stack_push(stk, b % a);
            }
            else {
                cout << "Error" << endl;
                return 1;
            }
        }
        else if (operation == "dup") {
            int top = stack_get(stk);
            stack_push(stk, top);
        }
        else if (operation == "drop") {
            stack_pop(stk);
        }
        else if (operation == "swap") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            stack_push(stk, a);
            stack_push(stk, b);
        }
        else if (operation == "over") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            stack_push(stk, b);
            stack_push(stk, a);
            stack_push(stk, b);
        }
        else if (operation == "rot") {
            int a = stack_get(stk); stack_pop(stk);
            int b = stack_get(stk); stack_pop(stk);
            int c = stack_get(stk); stack_pop(stk);
            stack_push(stk, b);
            stack_push(stk, a);
            stack_push(stk, c);
        }
        else if (operation == ".") {
            cout << stack_get(stk) << endl;
            stack_pop(stk);
        }
        else {
            stack_push(stk, stoi(operation));
        }
    }
    stack_delete(stk);
    return 0;
}
