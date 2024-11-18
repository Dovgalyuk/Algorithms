#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;

int main(__attribute__((unused)) int argc, char** argv){
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    Stack *stack = stack_create();
    char c;
    int flag = 0;

    while(input.get(c)) {
        if(c == '(' || c == '[' || c == '{') {
            stack_push(stack, c);
        } else if(c == ')' || c == ']' || c == '}') {
            if(stack_empty(stack)) {
                flag++;
                break;
            }

            char top = stack_get(stack);
            if((c == ')' && top == '(') || 
               (c == ']' && top == '[') || 
               (c == '}' && top == '{')) {
                stack_pop(stack);
            } else {
                flag++;
                break;
            }
        }
    }


    if(flag || !stack_empty(stack)) {
        cout << "NO";
    } else {
        cout << "YES";
    }

    input.close();
    stack_delete(stack);
    return 0;           
}
