#include <iostream>
#include <string>
#include <fstream>
#include "stack.h"

using namespace std;

int main()
{
    Stack *stack = stack_create();
    int A = 0, B = 0, C = 0, D = 0;
    char reg;
    string cmd, value;
    ifstream input;
    
    input.open("input.txt");
        
        //inserting commands
        do{
            input >> cmd;
            if (input.eof()) break;
           
            if (cmd == "push"){
            
                input >> value;

                if (value == "a"){
                    stack_push(stack, A);
                } else if (value == "b"){
                    stack_push(stack, B);
                } else if (value == "c"){
                    stack_push(stack, C);
                } else if (value == "d"){
                    stack_push(stack, D);
                } else {
                    stack_push(stack,atoi(value.c_str()));
                }
            }
            
            if (cmd == "pop") {
                input >> reg;
            
         
                if (reg == 'a'){
                    A = stack_get(stack);
                    stack_pop(stack);
                }
                if (reg == 'b'){
                    B = stack_get(stack);
                    stack_pop(stack);
                }
                if (reg == 'c'){
                    C = stack_get(stack);
                    stack_pop(stack);
                }
               
                if (reg == 'd'){
                    D = stack_get(stack);
                    stack_pop(stack);
                }
        
            }
            
        }while (!input.eof());
  
        cout << "A = " << A << "\n";
        cout << "B = " << B << "\n";
        cout << "C = " << C << "\n";
        cout << "D = " << D << "\n";
    
    input.close();
    stack_delete(stack);
    
    return 0;
}
