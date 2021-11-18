#include <iostream>
#include "stack.h"
#include <string>
int main(){

    Stack*stack = stack_create();    
    //std::string NO = (")"
    //std::string YES = ([]"")
    std::string b;
    getline(std::cin,b);
    int a = b.length();
    for (int i= 0; i < a;++i){
        if (stack_empty(stack)) stack_push(stack,b[i]);
        else if (b[i] == ']'){
            if (stack_get(stack) == '[') stack_pop(stack);
            else  stack_push(stack,b[i]);
        }
        else if (b[i]=='"'){
            if (stack_get(stack) == '"') stack_pop(stack);
            else  stack_push(stack,b[i]);
        }
        else if (b[i]==')'){
            if (stack_get(stack) == '(') stack_pop(stack);
            else  stack_push(stack,b[i]);
        }
        else  stack_push(stack,b[i]);
    } 
    if (stack_empty(stack)) std::cout << "YES\n";
    else std::cout << "NO\n";
    stack_delete(stack);
    return 0;
}