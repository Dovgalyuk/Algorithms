#include "lab2.h"

bool is_open(char c)
{
    if(c == '(' || c == '{' || c == '[' || c == '<')
        return true;

    return false;
}

char opposite(char c)
{
    if(c == '(')
        return c + 1;
    else if(c == ')')
        return c - 1;

    if(c == '[' || c == '{' || c == '<')
        return c + 2;
    else if(c == ']' || c == '}' || c == '>')
        return c - 2;

    return 1;
}

std::string task(std::ifstream& input)
{
    std::string str;
    if(input.is_open())
        input >> str;
        
    if(!is_open(str[0])) return "NO";

    Stack *stack = stack_create();
    for(size_t i = 0; i < str.size(); i++)
    {
        if(is_open(str[i]))
        {
            stack_push(stack, opposite(str[i]));
        }
        else
        {
            if(str[i] != stack_get(stack))
            {
                stack_delete(stack);
                return "NO";
            }
            else
                stack_pop(stack);
        }
    }
    
    if(!stack_empty(stack))
    {
        stack_delete(stack);
        return "NO";
    }
    else
    {
        stack_delete(stack);
        return "YES";
    }
}