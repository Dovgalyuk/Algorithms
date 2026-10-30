#include <iostream>
#include <stdexcept>
#include "stack.h"

int main()
{
    Stack<int> stack;
    if (!stack.empty() || stack.size() != 0)
        return 1;

    stack.push(10);
    stack.push(20);
    stack.push(30);
    if (stack.get() != 30 || stack.size() != 3)
        return 1;

    Stack<int> copy(stack);
    stack.pop();
    if (stack.get() != 20 || copy.get() != 30)
        return 1;

    Stack<int> assigned;
    assigned = copy;
    copy.pop();
    if (assigned.get() != 30 || copy.get() != 20)
        return 1;

    assigned = assigned;
    if (assigned.size() != 3 || assigned.get() != 30)
        return 1;

    assigned.pop();
    assigned.pop();
    assigned.pop();
    if (!assigned.empty())
        return 1;

    try
    {
        assigned.pop();
        return 1;
    }
    catch (const std::out_of_range&)
    {
    }

    std::cout << "Stack tests passed\n";
    return 0;
}
