#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;
 
int main(__attribute__((unused)) int argc, char** argv){
    ifstream input(argv[1]);
    Stack *stack = stack_create();
    string line;
    int flag = 0;
    char c;
    while (input.get(c)) {
        if (c == ')') {
            if (!stack_empty(stack) && stack_get(stack) == '(') {
                stack_pop(stack);
            } else {
                flag = 1;
                break;
            }
        } else if (c == '(') {
            stack_push(stack, c);
        } else if (c == '\'') {
            if (!stack_empty(stack) && stack_get(stack) == '\'') {
                stack_pop(stack);
            } else {
                stack_push(stack, c);
            }
        } else if (c == '\"') {
            if (!stack_empty(stack) && stack_get(stack) == '\"') {
                stack_pop(stack);
            } else {
                stack_push(stack, c);
            }
        }

    }

    if (flag || !stack_empty(stack)) {
        cout << "NO";
    } else {
        cout << "YES";
    }

    stack_delete(stack);
    return 0;           
}
