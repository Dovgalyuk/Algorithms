#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "stack.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        return 1;
    }

    ifstream script(argv[1]);
    ifstream input(argv[2]);

    if (!script || !input)
    {
        return 1;
    }

    vector<string> commands;
    string command;

    while (script >> command)
    {
        commands.push_back(command);
    }

    Stack* stack = stack_create();

    int repeatCount = 0;
    size_t repeatStart = 0;

    size_t i = 0;

    while (i < commands.size())
    {
        command = commands[i];

        bool isNumber = true;
        size_t start = 0;

        if (!command.empty() && command[0] == '-')
        {
            start = 1;
        }

        if (start == command.size())
        {
            isNumber = false;
        }

        for (size_t j = start; j < command.size(); ++j)
        {
            if (command[j] < '0' || command[j] > '9')
            {
                isNumber = false;
                break;
            }
        }

        if (isNumber)
        {
            int number = stoi(command);
            stack_push(stack, number);

            ++i;
            continue;
        }

        if (command == "get")
        {
            int value;

            if (!(input >> value))
            {
                stack_delete(stack);
                return 1;
            }

            stack_push(stack, value);
        }

        else if (command == "peek")
        {
            if (stack_empty(stack))
            {
                stack_delete(stack);
                return 1;
            }

            cout << stack_get(stack) << ' ';
        }

        else if (command == "add")
        {
            int first = stack_get(stack);
            stack_pop(stack);

            int second = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, first + second);
        }

        else if (command == "sub")
        {
            int first = stack_get(stack);
            stack_pop(stack);

            int second = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, first - second);
        }

        else if (command == "mul")
        {
            int first = stack_get(stack);
            stack_pop(stack);

            int second = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, first * second);
        }

        else if (command == "div")
        {
            int first = stack_get(stack);
            stack_pop(stack);

            int second = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, first / second);
        }

        else if (command == "sqrt")
        {
            int value = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, (int)sqrt(value));
        }

        else if (command == "sq")
        {
            int value = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, value * value);
        }

        else if (command == "cond")
        {
            if (stack_empty(stack))
            {
                stack_delete(stack);
                return 1;
            }

            int first = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                stack_delete(stack);
                return 1;
            }

            int second = stack_get(stack);

            if (first == second)
            {
                stack_pop(stack);
            }
            else
            {
                int depth = 1;

                while (depth > 0)
                {
                    ++i;

                    if (i >= commands.size())
                    {
                        stack_delete(stack);
                        return 1;
                    }

                    if (commands[i] == "cond")
                    {
                        depth++;
                    }
                    else if (commands[i] == "end")
                    {
                        depth--;
                    }
                }
            }
        }

        else if (command == "end")
        {
        }

        else if (command == "setr")
        {
            repeatCount = stack_get(stack);
            stack_pop(stack);

            repeatStart = i + 1;
        }

        else if (command == "repeat")
        {
            repeatCount--;

            if (repeatCount > 0)
            {
                i = repeatStart;
                continue;
            }
        }

        ++i;
    }

    cout << '\n';

    stack_delete(stack);

    return 0;
}
