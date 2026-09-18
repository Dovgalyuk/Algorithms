#include <iostream>
#include "stack.h"

int main()
{
    Stack *stack = stack_create();

    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);

    if (stack_get(stack) != 3)
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);

    if (stack_get(stack) != 2)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);

    if (stack_get(stack) != 1)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_push(stack, 4);
    stack_push(stack, 5);

    if (stack_get(stack) != 5)
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
