#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include "stack.h"

bool is_number(const std::string& str)
{
    if (str.empty()) return false;
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) return false;
        start = 1;
    }
    for (size_t i = start; i < str.length(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        return 1;
    }
    Stack* stack = stack_create();
    std::string str;
    while (file >> str)
    {
        if (is_number(str)) {
            Data val = static_cast<Data>(std::stoi(str));
            stack_push(stack, val);
        }
        else if (str == "+")
        {
            if (!stack_empty(stack))
            {
                Data y = stack_get(stack); 
                stack_pop(stack);
                if (!stack_empty(stack))
                {
                    Data x = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, x + y);
                }
            }
        }
        else if (str == "-")
        {
            if (!stack_empty(stack))
            {
                Data y = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack))
                {
                    Data x = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, x - y);
                }
            }
        }
        else if (str == "*")
        {
            if (!stack_empty(stack))
            {
                Data y = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack))
                {
                    Data x = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, x * y);
                }
            }
        }
        else if (str == "/")
        {
            if (!stack_empty(stack))
            {
                Data y = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack) && y != 0)
                {
                    Data x = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, x / y);
                }
            }
        }
        else if (str == "%")
        {
            if (!stack_empty(stack))
            {
                Data y = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack) && y != 0)
                {
                    Data x = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, x % y);
                }
            }
        }
        else if (str == "dup")
        {
            if (!stack_empty(stack)) stack_push(stack, stack_get(stack));
        }
        else if (str == "drop")
        {
            if (!stack_empty(stack)) stack_pop(stack);
        }
        else if (str == "swap")
        {
            if (!stack_empty(stack))
            {
                Data y = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack))
                {
                    Data x = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, y);
                    stack_push(stack, x);
                }
            }
        }
        else if (str == "over")
        {
            if (!stack_empty(stack))
            {
                Data y = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack))
                {
                    Data x = stack_get(stack);
                    stack_push(stack, y);
                    stack_push(stack, x);
                }
            }
        }
        else if (str == "rot")
        {
            if (!stack_empty(stack))
            {
                Data c = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack))
                {
                    Data y = stack_get(stack);
                    stack_pop(stack);
                    if (!stack_empty(stack))
                    {
                        Data x = stack_get(stack);
                        stack_pop(stack);
                        stack_push(stack, y);
                        stack_push(stack, c);
                        stack_push(stack, x);
                    }
                }
            }
        }
        else if (str == ".")
        {
            if (!stack_empty(stack))
            {
                std::cout << stack_get(stack) << std::endl;
                stack_pop(stack);
            }
        }
    }

    stack_delete(stack);
    return 0;
}