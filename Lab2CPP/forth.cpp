#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

#include "stack.h"

int take(Stack<int> &stack)
{
    int value = stack.get();
    stack.pop();

    return value;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Expected input file\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    try
    {
        Stack<int> stack;
        std::string command;

        while (input >> command)
        {
            if (command.size() == 1 &&
                command[0] >= '0' && command[0] <= '9')
            {
                stack.push(command[0] - '0');
            }
            else if (command == "dup")
            {
                stack.push(stack.get());
            }
            else if (command == "drop")
            {
                stack.pop();
            }
            else if (command == "swap")
            {
                int top = take(stack);
                int below = take(stack);

                stack.push(top);
                stack.push(below);
            }
            else if (command == "over")
            {
                int top = take(stack);
                int below = stack.get();

                stack.push(top);
                stack.push(below);
            }
            else if (command == "rot")
            {
                int top = take(stack);
                int middle = take(stack);
                int bottom = take(stack);

                stack.push(middle);
                stack.push(top);
                stack.push(bottom);
            }
            else if (command == ".")
            {
                std::cout << take(stack) << '\n';
            }
            else if (command == "+" || command == "-" ||
                     command == "*" || command == "/" ||
                     command == "%")
            {
                long long right = take(stack);
                long long left = take(stack);
                long long result;

                if ((command == "/" || command == "%") &&
                    right == 0)
                {
                    throw std::runtime_error("Division by zero");
                }

                if (command == "+")
                {
                    result = left + right;
                }
                else if (command == "-")
                {
                    result = left - right;
                }
                else if (command == "*")
                {
                    result = left * right;
                }
                else if (command == "/")
                {
                    result = left / right;
                }
                else
                {
                    result = left % right;
                }

                if (result < std::numeric_limits<int>::min() ||
                    result > std::numeric_limits<int>::max())
                {
                    throw std::runtime_error("Integer overflow");
                }

                stack.push(static_cast<int>(result));
            }
            else
            {
                throw std::runtime_error(
                    "Unknown command: " + command);
            }
        }

        if (!input.eof())
        {
            throw std::runtime_error("Cannot read input file");
        }
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}