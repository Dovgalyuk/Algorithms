#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

bool pair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}') ||
           (open == '<' && close == '>');
}

bool subsequence(const std::string &sequence)
{
    Stack *stack = stack_create();

    for (char ch : sequence)
    {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
        {
            stack_push(stack, ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}' || ch == '>')
        {
            if (stack_empty(stack) || !pair(stack_get(stack), ch))
            {
                stack_delete(stack);
                return false;
            }
            stack_pop(stack);
        }
    }

    bool valid = stack_empty(stack);
    stack_delete(stack);
    return valid;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Failed to open the file: " << argv[1] << std::endl;
        return 1;
    }

    std::string sequence;
    std::getline(input, sequence);

    if (subsequence(sequence))
    {
        std::cout << "YES" << std::endl;
    }
    else
    {
        std::cout << "NO" << std::endl;
    }

    input.close();
    return 0;
}