#include <iostream>
#include "stack.cpp"
#include <string>
int main(){

    Stack*stack = stack_create();    
    //std::string NO = (")";
    //std::string YES = ([]"");
    std::string b= "([]"")";
    std::cout << b.length()<<std::endl;
    for (int i=0; i <= b.length();++i){
        stack_push(stack,b[b.length()-i]);
    }
    std::string f;
    for (int i=0;i<b.length();++i){
        f[i]=stack_get(stack);
        stack_pop(stack);
    }
    if (f=="409193343441"){
        std::cout << "YES" << std::endl;
    }
    else if (f=="40344134"){
        std::cout << "NO" <<std::endl;
    }
    else std::cout << "unknown sequence";
    stack_delete(stack);
    system("pause");
    return 0;
}