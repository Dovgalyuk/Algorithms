#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int priority(char c)
{
    if(c == '+' || c == '-')
    {
        return 1;
    }

    if(c == '*')
    {
        return 2;
    }
    return 0;
}

void task(std::string input)
{
    Stack* stack = stack_create();
    std::string output;

    for(size_t i = 0; i < input.size();i++)
    {
        char c = input[i];

        if(c >= '0' && c <= '9')
        {
            output += c;
        }
        else if(c == '(')
        {
            stack_push(stack, c);
        }
        else if(c == ')')
        {
            while(stack_get(stack) != '(')
            {
                output += stack_get(stack);
                stack_pop(stack);
            }
            stack_pop(stack);
        }
        else if(c == '+' || c == '-' || c == '*')
        {
            while(!stack_empty(stack) && priority(stack_get(stack) >= priority(c)))
            {
                output += stack_get(stack);
                stack_pop(stack);
            }
            stack_push(stack, c);
        }
    }

    while(!stack_empty(stack))
    {
        output += stack_get(stack);
        stack_pop(stack);
    }


    for(size_t i = 0; i < output.size(); i++)
    {
        char c = output[i];
        int A, B;

        if(c >= '0' && c <= '9')
        {
            std::cout << "PUSH " << c << std::endl;
            stack_push(stack, c);
        }
        else if(c == '+' || c == '-' || c == '*')
        {
            std::cout << "POP A" << std::endl;
            std::cout << "POP B" << std::endl;
            A = stack_get(stack);
            stack_pop(stack);
            B = stack_get(stack);
            stack_pop(stack);
            
            if(c == '+')
            {
                std::cout << "ADD A, B" << std::endl;
                A = A + B;
            }
            else if(c == '-')
            {
                std::cout << "SUB A, B" << std::endl;
                A = A - B;
            }
            else if(c == '*')
            {
                std::cout << "MUL A, B" << std::endl;
                A = A * B;
            }

            std::cout << "PUSH A" << std::endl;
            stack_push(stack, A);
        }
    }
    stack_delete(stack);
}

int main(int argc, char **argv)
{
    std::ifstream in(argv[1]);
    std::string input;
    getline(in, input);
    task(input);
    in.close();
}