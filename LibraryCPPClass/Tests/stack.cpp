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

    
    stack.push(3);
    if (stack.get() != 3)
    {
        std::cout << "Invalid stack push after empty\n";
        return 1;
    }

    stack.pop();
    if (!stack.empty())
    {
        std::cout << "Invalid stack empty\n";
        return 1;
    }

    try 
    {
        stack.get();
        std::cout << "Invalid stack empty\n";
        return 1;
    }
    catch (const std::exception& e) 
    {
        std::cout << "Exception from empty stack on get : " << e.what() << "\n";
    }

    try 
    {
        stack.pop();
        std::cout << "Invalid stack empty\n";
        return 1;
    }
    catch (const std::exception& e) 
    {
        std::cout << "Exception from empty stack on pop: " << e.what() << "\n";
    }

    stack.push(5);
    stack.push(7);
    stack.push(8);
    if (stack.get() != 8)
    {
        std::cout << "Invalid stack top after multiple pushes\n";
        return 1;
    }

    stack.pop();
    if (stack.get() != 7)
    {
        std::cout << "Invalid stack top after pop\n";
        return 1;
    }

    stack.pop();
    stack.pop();
    if (!stack.empty())
    {
        std::cout << "Invalid stack empty after pops\n";
        return 1;
    }

}
