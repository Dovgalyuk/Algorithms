#include <iostream>
#include "stack.cpp"
#include <string>
int main(){

    Stack*stack = stack_create();    
    //std::string NO = (")";
    //std::string YES = ([]"");
    std::string b;
    int k2=0;//для скобок
    getline(std::cin,b);
    for (int i=0; i <= b.length();++i){
        stack_push(stack,b[b.length()-i]);
        if ((stack_get(stack)==')') && ( i==1)) k2=1;
        if ((stack_get(stack)=='(') && ( i==b.length()) && (k2==1)) {
            std::cout << "YES\n";
            k2=2;
            break;
        }
    }
    std::cout << k2;
    if (k2!=2) std::cout << "NO\n";
    system("pause");
    stack_delete(stack);
    return 0;
}