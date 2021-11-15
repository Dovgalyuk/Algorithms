#include <iostream>
#include "stack.h"
#include <string>
int main(){

    Stack*stack = stack_create();    
    //std::string NO = (")"
    //std::string YES = ([]"")
    std::string b;
        getline(std::cin,b);
    for (int i= 0; i <= b.length();++i){
        if (stack_empty(stack)) stack_push(stack,b[i]);
        else if (b[i] == ']'){
            if (stack_get(stack) == '[') stack_pop(stack);
            if (stack_empty(stack)) break;
        }
        else if (b[i]=='"'){
            if (stack_get(stack) == '"') stack_pop(stack);
            if (stack_empty(stack)) break;
        }
        else if (b[i]==')'){
            if (stack_get(stack) == '(') stack_pop(stack);
            if (stack_empty(stack)) break;
        }
        else  stack_push(stack,b[i]);
    }         
    if (stack_empty(stack)) std::cout << "YES\n";
    else std::cout << "NO\n";
    system("pause");
    stack_delete(stack);
    return 0;
}