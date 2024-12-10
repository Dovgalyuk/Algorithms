#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
#include "vector.h"

void task1(std::ifstream& input)
{
    std::string command;
    Stack* stack1 = stack_create();
    int var0 = 0, var1 = 0, var2= 0, var3 = 0;
    while ((input >> command)) {
		std::cout << "\n" << command;
        //bipush
        if(command == "bipush") {
            if(!(input >> command)) {
                std::cout << "error";
                return;
                }
            std::cout << " " << command;
            stack_push(stack1, stoi(command));   
        }
        //pop
        else if(command == "pop") {
            stack_pop(stack1);   
        }
        //imul
        else if(command == "imul") {
            int mul = 0;

            mul = stack_get(stack1);
            stack_pop(stack1);
            mul *= stack_get(stack1);
            stack_pop(stack1);
            stack_push(stack1, mul); 
        }
        //iand
        else if(command == "iand") {
            int mul = 0;

            mul = stack_get(stack1);
            stack_pop(stack1);
            mul =mul & stack_get(stack1);
            stack_pop(stack1);
            stack_push(stack1, mul);   
        }
        //ior
        else if(command == "ior") {
            int mul = 0;

            mul = stack_get(stack1);
            stack_pop(stack1);
            mul = mul | stack_get(stack1);
            stack_pop(stack1);
            stack_push(stack1, mul);    
        }
        //ixor
        else if(command == "ixor") {
            int mul = 0;

            mul = stack_get(stack1);
            stack_pop(stack1);
            mul = mul ^ stack_get(stack1);
            stack_pop(stack1);
            stack_push(stack1, mul);    
        }
        //iadd
        else if(command == "iadd") {
            int sum = 0;

            sum += stack_get(stack1);
            stack_pop(stack1);
            sum += stack_get(stack1);
            stack_pop(stack1);
            stack_push(stack1, sum);
        }
        //isub
        else if(command == "isub") {
            int sub = 0;

            sub = stack_get(stack1);
            stack_pop(stack1);
            sub -= stack_get(stack1);
            stack_pop(stack1);
            stack_push(stack1, sub);  
        }
        //iload_0
        else if(command == "iload_0") {
            stack_push(stack1, var0);   
        }
        //iload_1
        else if(command == "iload_1") {
            
            stack_push(stack1, var1);    
        }
        //iload_2
        else if(command == "iload_2") {
            
            stack_push(stack1, var2);     
        }
        //iload_3
        else if(command == "iload_3") {
            
            stack_push(stack1, var3);     
        }
        //istore_0
        else if(command == "istore_0") {
            var0 = stack_get(stack1);
            stack_pop(stack1);  
        }
        //istore_0
        else if(command == "istore_0") {
            var0 = stack_get(stack1);
            stack_pop(stack1);   
        }
        //istore_1
        else if(command == "istore_1") {
            var1 = stack_get(stack1);
            stack_pop(stack1);   
        }
        //istore_2
        else if(command == "istore_2") {
            var2 = stack_get(stack1);
            stack_pop(stack1);   
        }
        //istore_3
        else if(command == "istore_3") {
            var3 = stack_get(stack1);
            stack_pop(stack1);   
        }
        //swap
        else if(command == "swap") {
            int tmp1, tmp2;
            tmp1 = stack_get(stack1);
            stack_pop(stack1);
            tmp2 = stack_get(stack1);
            stack_pop(stack1);
            stack_push(stack1, tmp1);
            stack_push(stack1, tmp2);
        }

	}
    std::cout << "\n\n------------------------\nstack:\n";
    Stack* stack2 = stack_create();
    while(!stack_empty(stack1)) {
        stack_push(stack2, stack_get(stack1));
        stack_pop(stack1);
    }
    while(!stack_empty(stack2)) {
        std::cout << stack_get(stack2) << " ";
        stack_pop(stack2);
    }
    
    std::cout << "\n\nvars:\n" << var0 << "\n"<< var1 << "\n"<< var2 << "\n"<< var3;
    stack_delete(stack1);
    stack_delete(stack2);
}

int main(int argc, char **argv)
{
    //std::ifstream input("input.txt");
    if(argc != 2) return 1;
    std::ifstream input(argv[1]);
	if (input.is_open()) {
        //Stack* stack1 = stack_create();
	    task1(input);
    }
	input.close();
    	return 0;
}