#include <iostream>
#include "stack.h"

int main()
{
    Stack* stack = stack_create();

    stack_push(stack, {1, false});
    stack_push(stack, {2, false});
    stack_push(stack, {3, false});

    if (stack_get(stack).value != 3)
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack).value << "\n";
    stack_pop(stack);

    if (stack_get(stack).value != 2)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack).value << "\n";
    stack_pop(stack);

    if (stack_get(stack).value != 1)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack).value << "\n";
    stack_pop(stack);

    stack_push(stack, {4, false});
    stack_push(stack, {5, false});

    if (stack_get(stack).value != 5)
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    while (!stack_empty(stack))
    {
        std::cout << "Get: " << stack_get(stack).value << "\n";
        stack_pop(stack);
    }

    stack_delete(stack);
}