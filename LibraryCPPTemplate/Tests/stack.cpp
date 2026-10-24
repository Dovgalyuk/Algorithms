#include <iostream>
#include "stack.h"

typedef Stack<int> MyStack;

int main()
{
    MyStack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack = stack;

    if (stack.top() != 3)
    {
        std::cout << "Invalid stack top after push\n";
        return 1;
    }

    std::cout << "Top: " << stack.top() << "\n";
    stack.pop();

    if (stack.top() != 2)
    {
        std::cout << "Invalid stack top after pop\n";
        return 1;
    }

    std::cout << "Top: " << stack.top() << "\n";
    stack.pop();

    if (stack.top() != 1)
    {
        std::cout << "Invalid stack top after pop\n";
        return 1;
    }

    std::cout << "Top: " << stack.top() << "\n";
    stack.push(4);
    stack.push(5);

    if (stack.top() != 5)
    {
        std::cout << "Invalid stack top after push\n";
        return 1;
    }

    MyStack copy(stack);

    while (!stack.empty())
    {
        if (copy.empty() || stack.top() != copy.top())
        {
            std::cout << "Invalid stack copy\n";
            return 1;
        }

        std::cout << "Top: " << stack.top() << "\n";
        copy.pop();
        stack.pop();
    }

    if (!copy.empty())
    {
        std::cout << "Invalid stack copy size\n";
        return 1;
    }

    return 0;
}