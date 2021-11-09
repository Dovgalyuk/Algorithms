#include <iostream>
#include "stack.cpp"
#include <string>
int main(){

    Stack*stack = stack_create();    
    //std::string NO = (")";
    //std::string YES = ([]"");
    std::string b;
    getline(std::cin,b);
    for (int i=0; i <= b.length();++i){
        stack_push(stack,b[b.length()-i]);
    }
    std::string f;
    for (int i=0;i<b.length();++i){
        f.push_back(stack_get(stack));
        stack_pop(stack);
        
    }
    if ((f.find("([]"")")&&(f.length()==6))){
        std::cout << "YES" << std::endl;
    }
    else if ((f.find("(")"")&&(f.length()==4)){
        std::cout << "NO" <<std::endl;
    }
    stack_delete(stack);
    system("pause");
    return 0;
}