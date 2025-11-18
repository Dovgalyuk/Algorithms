#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int priority(char c)
{
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void toPostfix(const std::string& input)
{
    Stack* stack = stack_create();
    std::string output;

    for (size_t i = 0; i < input.size(); i++)
    {
        char c = input[i];

        if (c >= 'A' && c <= 'Z')  
        {
            output += c;
        }
        else if (c == '(')
        {
            stack_push(stack, c);
        }
        else if (c == ')')
        {
            while (!stack_empty(stack) && stack_get(stack) != '(')
            {
                output += stack_get(stack);
                stack_pop(stack);
            }
            if (!stack_empty(stack)) stack_pop(stack); 
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            while (!stack_empty(stack) && 
                   priority(stack_get(stack)) >= priority(c))
            {
                output += stack_get(stack);
                stack_pop(stack);
            }
            stack_push(stack, c);
        }
    }

    while (!stack_empty(stack))
    {
        output += stack_get(stack);
        stack_pop(stack);
    }

    stack_delete(stack);
    std::cout << output << std::endl;
}

int main(int argc, char** argv)
{
    std::ifstream in(argv[1]);
    std::string input;
    getline(in, input);

    toPostfix(input);

    in.close();
    return 0;
}
