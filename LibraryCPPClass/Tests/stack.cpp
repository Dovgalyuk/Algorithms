
#include <iostream>
#include "stack.h"

int main()
{
    Stack stack;

    if (!stack.empty())
    {
        std::cout << "Stack creation error\n";
        return 1;
    }

    stack.push(1);
    stack.push(2);
    stack.push(3);

    if (stack.get() != 3)
    {
        std::cout << "Stack push error\n";
        return 1;
    }

    stack = stack;

    if (stack.get() != 3)
    {
        std::cout << "Stack self-assignment error\n";
        return 1;
    }

    Stack copy(stack);

    if (copy.get() != 3)
    {
        std::cout << "Stack copy constructor error\n";
        return 1;
    }

    copy.pop();

    if (copy.get() != 2 || stack.get() != 3)
    {
        std::cout << "Stack copy independence error\n";
        return 1;
    }

    Stack assigned;
    assigned.push(10);
    assigned = stack;

    if (assigned.get() != 3)
    {
        std::cout << "Stack assignment error\n";
        return 1;
    }

    stack.pop();

    if (stack.get() != 2)
    {
        std::cout << "Stack pop error\n";
        return 1;
    }

    stack.pop();

    if (stack.get() != 1)
    {
        std::cout << "Stack pop error\n";
        return 1;
    }

    stack.pop();

    if (!stack.empty())
    {
        std::cout << "Stack empty error\n";
        return 1;
    }

    std::cout << "Stack tests passed\n";
    return 0;
}
