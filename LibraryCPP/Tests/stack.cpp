#include <iostream>
#include "stack.h"

int main()
{
    Stack* stack = stack_create();

    stack_push(stack, 'a');
    stack_push(stack, 'b');
    stack_push(stack, 'c');

    if (stack_get(stack) != 'c')
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);

    if (stack_get(stack) != 'b')
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);

    if (stack_get(stack) != 'a')
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_push(stack, 'q');
    stack_push(stack, 'w');

    if (stack_get(stack) != 'w')
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    while (!stack_empty(stack))
    {
        std::cout << "Get: " << stack_get(stack) << "\n";
        stack_pop(stack);
    }

    stack_delete(stack);
}