#include <stdexcept>
#include <iostream>
#include "stack.h"

bool checkStack()
{
    Stack stack;
    if (!stack.empty()) return false;
    try { stack.get(); return false; }
    catch (const std::out_of_range &) {}
    try { stack.pop(); return false; }
    catch (const std::out_of_range &) {}

    for (int i = 0; i < 10000; i++) stack.push(i);
    Stack copy(stack);
    Stack assigned;
    assigned.push(-1);
    assigned = stack;
    for (int i = 9999; i >= 0; i--)
    {
        if (stack.empty() || stack.get() != i) return false;
        stack.pop();
    }
    if (!stack.empty() || copy.get() != 9999 || assigned.get() != 9999) return false;
    copy.pop();
    if (copy.get() != 9998 || assigned.get() != 9999) return false;
    assigned = stack;
    return assigned.empty();
}
int main()
{
    if (!checkStack()) return 1;
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack = stack;

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
}
