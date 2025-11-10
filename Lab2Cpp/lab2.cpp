#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

void process_command(Stack *stack, const std::string &token)
{
    if (token.size() == 1 && token[0] >= '0' && token[0] <= '9')
    {
        stack_push(stack, token[0] - '0');
    }
    else if (token == "+")
    {
        int b = stack_get(stack);
        stack_pop(stack);
        int a = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, a + b);
    }
    else if (token == "-")
    {
        int b = stack_get(stack);
        stack_pop(stack);
        int a = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, a - b);
    }
    else if (token == "*")
    {
        int b = stack_get(stack);
        stack_pop(stack);
        int a = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, a * b);
    }
    else if (token == "/")
    {
        int b = stack_get(stack);
        stack_pop(stack);
        int a = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, a / b);
    }
    else if (token == "%")
    {
        int b = stack_get(stack);
        stack_pop(stack);
        int a = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, a % b);
    }
    else if (token == "dup")
    {
        int a = stack_get(stack);
        stack_push(stack, a);
    }
    else if (token == "drop")
    {
        stack_pop(stack);
    }
    else if (token == "swap")
    {
        int a = stack_get(stack);
        stack_pop(stack);
        int b = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, a);
        stack_push(stack, b);
    }
    else if (token == "over")
    {
        int a = stack_get(stack);
        stack_pop(stack);
        int b = stack_get(stack);
        stack_push(stack, a);
        stack_push(stack, b);
    }
    else if (token == "rot")
    {
        int c = stack_get(stack);
        stack_pop(stack);
        int b = stack_get(stack);
        stack_pop(stack);
        int a = stack_get(stack);
        stack_pop(stack);
        stack_push(stack, b);
        stack_push(stack, c);
        stack_push(stack, a);
    }
    else if (token == ".")
    {
        std::cout << stack_get(stack) << std::endl;
        stack_pop(stack);
    }
}

int main(int, char **argv)
{
    std::ifstream input(argv[1]);
    Stack *stack = stack_create();
    
    std::string line;
    while (std::getline(input, line))
    {
        std::string token;
        for (size_t i = 0; i < line.size(); i++)
        {
            char c = line[i];
            if (c == ' ')
            {
                if (token.size() > 0)
                {
                    process_command(stack, token);
                    token.clear();
                }
            }
            else
            {
                token += c;
            }
        }
        if (token.size() > 0)
        {
            process_command(stack, token);
        }
    }
    
    stack_delete(stack);
    input.close();
    return 0;
}
