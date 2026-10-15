
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include "stack.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: specify one input file\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file)
    {
        std::cerr << "Error: cannot open input file\n";
        return 1;
    }

    Stack* stack = stack_create();

    if (stack == nullptr)
    {
        std::cerr << "Error: cannot create stack\n";
        return 1;
    }

    char c;
    int a, b;
    bool error = false;

    while (file.get(c))
    {
        if (c >= '0' && c <= '9')
        {
            stack_push(stack, c - '0');
            continue;
        }

        if (std::isspace(static_cast<unsigned char>(c)))
            continue;

        switch (c)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '`':
            if (stack_empty(stack))
            {
                error = true;
                break;
            }

            a = stack_get(stack);

            if (c == '/' || c == '%')
            {
                if (a == 0)
                {
                    std::cerr << "Error: division by zero\n";
                    error = true;
                    break;
                }
            }

            stack_pop(stack);

            if (stack_empty(stack))
            {
                std::cerr << "Error: not enough values in stack\n";
                error = true;
                break;
            }

            b = stack_get(stack);
            stack_pop(stack);

            if (c == '+') stack_push(stack, b + a);
            if (c == '-') stack_push(stack, b - a);
            if (c == '*') stack_push(stack, b * a);
            if (c == '/') stack_push(stack, b / a);
            if (c == '%') stack_push(stack, b % a);
            if (c == '`') stack_push(stack, b > a ? 1 : 0);

            break;

        case '!':
            if (stack_empty(stack))
            {
                std::cerr << "Error: stack is empty\n";
                error = true;
                break;
            }

            a = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a == 0 ? 1 : 0);
            break;

        case ':':
            if (stack_empty(stack))
            {
                std::cerr << "Error: stack is empty\n";
                error = true;
                break;
            }

            stack_push(stack, stack_get(stack));
            break;

        case '.':
            if (stack_empty(stack))
            {
                std::cerr << "Error: stack is empty\n";
                error = true;
                break;
            }

            std::cout << stack_get(stack) << '\n';
            stack_pop(stack);
            break;

        case '&':
            stack_push(stack, std::rand() % 100);
            break;

        default:
            std::cerr << "Error: unknown command '" << c << "'\n";
            error = true;
            break;
        }

        if (error)
            break;
    }

    stack_delete(stack);

    return error ? 1 : 0;
}
