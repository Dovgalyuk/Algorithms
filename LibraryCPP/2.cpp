#include <iostream>
#include "stack.cpp"
#include <string>
int main(){

    Stack*stack = stack_create();    
    //std::string NO = (")"
    //std::string YES = ([]"")
    std::string b;
        getline(std::cin,b);
    for (int i= 1; i <= b.length();++i){
        //std::cout << 1;
        if ((b[b.length()-i] == '[') && (stack_get(stack)==']')){
            stack_pop(stack);
            i++;
        }
        //std::cout << 1;
        if ((b[b.length()-i] == '"') && (stack_get(stack)=='"')){
            std::cout << 2;
            stack_pop(stack);
            i++;
        }
        //std::cout << 1;
        if ((b[b.length()-i] == '(') && (stack_get(stack)==')'))
        {
            stack_pop(stack);
        }
        else stack_push(stack,b[b.length()-i]);
    
    }    
    if (stack_empty(stack)) std::cout << "YES\n";
    else std::cout << "NO\n";
    system("pause");
    stack_delete(stack);
    return 0;
}