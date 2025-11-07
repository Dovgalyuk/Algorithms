#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
using namespace std;

int priority_operations(char ch){
    if(ch == '+' || ch == '-'){
        return 1;
    } else if(ch == '*' || ch == '/'){
        return 2;
    }
    return 0;
}

void task_1(string input){
    Stack *stack = stack_create();
    string output;

    for(size_t i = 0; i < input.size(); i++){
        char ch = input[i];

        if(ch >= 'A' && ch <= 'Z'){
            output += ch;

        } else if(ch == '+' || ch == '-' || ch == '*' || ch == '/'){
            while(!stack_empty(stack) && priority_operations(stack_get(stack)) >= priority_operations(ch) && stack_get(stack) != '('){
                output += stack_get(stack);
                stack_pop(stack);
            }
            stack_push(stack, ch);

        } else if(ch == '('){
            stack_push(stack, ch);

        } else if(ch == ')'){
            while(!stack_empty(stack) && stack_get(stack) != '('){
                output += stack_get(stack);
                stack_pop(stack);
            } 
            if(stack_empty(stack)){
                cout << "Выражение не коректно"<< endl;
                stack_delete(stack);
                return;
            } else {
               stack_pop(stack); 
            }
        } 
    }
    while(!stack_empty(stack)){
        output += stack_get(stack);
        stack_pop(stack);
    }
    stack_delete(stack);
    cout << output;
}


int main(int argc, char **argv)
{
    std::ifstream in(argv[1]);
    std::string input;
    getline(in, input);
    task_1(input);
    in.close();
}