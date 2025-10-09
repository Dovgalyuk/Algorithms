#include <iostream>
#include <cstdlib>
#include "stack.h"
#include <fstream>
#include <sstream>

bool safe(Stack* stack, Data& n){
    if(stack_empty(stack)) return false;
    n = stack_get(stack);
    stack_pop(stack);
    return true;
}

Data add(Data a, Data b){ return a + b; }
Data sub(Data a, Data b){ return a - b; } 
Data mul(Data a, Data b){ return a * b; }
Data divide(Data a, Data b){ return b != 0 ? a / b : 0; }
Data modul(Data a, Data b){ return b != 0 ? a % b : 0; }
Data greater(Data a, Data b){ return a > b ? 1 : 0; }
Data lognot(Data a){ return a == 0 ? 1 : 0; }

void bin_op(Stack* stack, Data (*op)(Data, Data)){
    Data a, b;
    if(safe(stack, b) && safe(stack, a)) stack_push(stack, op(a,b));
}

void un_op(Stack* stack, Data (*op)(Data)){
    Data a;
    if(safe(stack, a)) stack_push(stack, op(a));
}

void dupl(Stack* stack){
    if(!stack_empty(stack)){
        Data a = stack_get(stack);
        stack_push(stack, a);
    }
}

void print_pop(Stack* stack){
    Data a;
    if(safe(stack, a)) std::cout << a << std::endl;
}

void interpretBefunge(const std::string& str){
    Stack* stack = stack_create();
    for(char c : str){
        if(c >= '0' && c <= '9'){
            stack_push(stack, c - '0');
        } else {
            switch(c){
                case '+': bin_op(stack, add); break;
                case '-': bin_op(stack, sub); break;
                case '*': bin_op(stack, mul); break;
                case '/': bin_op(stack, divide); break;
                case '%': bin_op(stack, modul); break;
                case '!': un_op(stack, lognot); break;
                case '`': bin_op(stack, greater); break;
                case ':': dupl(stack); break;
                case '.': print_pop(stack); break;
                case '&': stack_push(stack, rand());
            }
        }
    }
    stack_delete(stack);
}

int main(int argc, char* argv[]){
    std::ifstream file(argv[1]);
    std::stringstream b;
    b << file.rdbuf();
    std::string str = b.str();
    interpretBefunge(str);
    return 0;
}