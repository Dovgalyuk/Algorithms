#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

int priority(char op)
{
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool is_operator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

void task(const std::string &expr)
{
    Stack *stack = stack_create();
    std::string output;
    bool error = false;

    for (size_t i = 0; i < expr.size(); ++i)
    {
        char c = expr[i];

        if (std::isalpha((unsigned char)c))
        {
            output += c;
        }
        else if (c == '(')
        {
            stack_push(stack, c);
        }
        else if (c == ')')
        {
            bool found_open = false;
            while (!stack_empty(stack))
            {
                char current = (char)stack_get(stack);
                stack_pop(stack);
                if (current == '(')
                {
                    found_open = true;
                    break;
                }
                output += current;
            }
            if (!found_open)
            {
                error = true;
                break;
            }
        }
        else if (is_operator(c))
        {
            while (!stack_empty(stack))
            {
                char current = (char)stack_get(stack);
                if (priority(current) >= priority(c))
                {
                    output += current;
                    stack_pop(stack);
                }
                else
                {
                    break;
                }
            }
            stack_push(stack, c);
        }
        else if (std::isspace((unsigned char)c))
        {
            continue;
        }
        else
        {
            error = true;
            break;
        }
    }

    while (!error && !stack_empty(stack))
    {
        char current  = (char)stack_get(stack);
        stack_pop(stack);
        if (current == '(')
        {
            error = true;
            break;
        }
        output += current;
    }

    stack_delete(stack);

    if (error)
        std::cout << "Error: invalid expression\n";
    else
        std::cout << output << "\n";
}

int main(int argc, char **argv)
{
    (void)argc;
    std::ifstream input(argv[1]);

    std::string expr;
    std::getline(input, expr);

    task(expr);

    return 0;
}