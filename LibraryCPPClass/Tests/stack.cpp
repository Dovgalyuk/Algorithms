#include <iostream>
#include "stack.h"

int main()
{
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    if (stack.get() != 3)
    {
        std::cout << "Invalid stack top after push\n";
        return 1;
    }

    std::cout << "Get: " << stack.get() << "\n";
    stack.pop();

    if (stack.get() != 2)
    {
        std::cout << "Invalid stack top after pop\n";
        return 1;
    }

    std::cout << "Get: " << stack.get() << "\n";
    stack.pop();

    if (stack.get() != 1)
    {
        std::cout << "Invalid stack top after pop\n";
        return 1;
    }

    std::cout << "Get: " << stack.get() << "\n";
    stack.push(4);
    stack.push(5);

    if (stack.get() != 5)
    {
        std::cout << "Invalid stack top after push\n";
        return 1;
    }

    while (!stack.empty())
    {
        std::cout << "Get: " << stack.get() << "\n";
        stack.pop();
    }

    stack.push(7);
    if (stack.get() != 7)
    {
        std::cout << "Error: push after empty stack\n";
        return 1;
    }

    stack.pop();
    if (!stack.empty())
    {
        std::cout << "Error: stack should be empty\n";
        return 1;
    }

    try {
        stack.get();
        std::cout << "Error: stack should be empty\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cout << "Expected exception on get from empty stack: " << e.what() << "\n";
    }

    try {
        stack.pop();
        std::cout << "Error: stack should be empty\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cout << "Expected exception on pop from empty stack: " << e.what() << "\n";
    }

    stack.push(8);
    stack.push(9);
    stack.push(10);
    if (stack.get() != 10)
    {
        std::cout << "Invalid stack top after multiple pushes\n";
        return 1;
    }

    stack.pop();
    if (stack.get() != 9)
    {
        std::cout << "Invalid stack top after pop\n";
        return 1;
    }

    stack.pop();
    stack.pop();
    if (!stack.empty())
    {
        std::cout << "Error: stack should be empty after pops\n";
        return 1;
    }

    return 0;
}
