#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "stack.h"

Data parse_number(const std::string &text)
{
    return (Data)std::atoi(text.c_str());
}

int main(int argc, char **argv)
{
    (void)argc;

    std::ifstream script(argv[1]);
    std::ifstream data(argv[2]);

    std::vector<std::string> commands;
    std::string word;
    while (script >> word)
    {
        commands.push_back(word);
    }

    Stack *stack = stack_create();

    int loop_var = 0;
    int loop_start = -1;

    for (size_t i = 0; i < commands.size(); ++i)
    {
        const std::string &c = commands[i];

        if (c == "get")
        {
            Data x;
            if (data >> x)
            {
                stack_push(stack, x);
            }
        }
        else if (c == "add")
        {
            Data a = stack_get(stack);
            stack_pop(stack);
            Data b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a + b);
        }
        else if (c == "sub")
        {
            Data a = stack_get(stack);
            stack_pop(stack);
            Data b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a - b);
        }
        else if (c == "mul")
        {
            Data a = stack_get(stack);
            stack_pop(stack);
            Data b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a * b);
        }
        else if (c == "div")
        {
            Data a = stack_get(stack);
            stack_pop(stack);
            Data b = stack_get(stack);
            stack_pop(stack);
            if (b != 0)
            {
                stack_push(stack, a / b);
            }
        }
        else if (c == "sqrt")
        {
            Data a = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, (Data)std::sqrt((double)a));
        }
        else if (c == "sq")
        {
            Data a = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a * a);
        }
        else if (c == "peek")
        {
            std::cout << stack_get(stack) << " ";
        }
        else if (c == "cond")
        {
            Data a = stack_get(stack);
            stack_pop(stack);
            if (!stack_empty(stack) && stack_get(stack) == a)
            {
                stack_pop(stack);
            }
            else
            {
                while (i < commands.size() && commands[i] != "end")
                {
                    ++i;
                }
            }
        }
        else if (c == "end")
        {
        }
        else if (c == "setr")
        {
            Data value = stack_get(stack);
            stack_pop(stack);
            loop_var = value;
            loop_start = (int)i + 1;
        }
        else if (c == "repeat")
        {
            if (loop_var > 0 && loop_start >= 0)
            {
                --loop_var;
                i = (size_t)loop_start - 1;
            }
        }
        else
        {
            stack_push(stack, parse_number(c));
        }
    }

    std::cout << "\n";

    stack_delete(stack);
    return 0;
}
