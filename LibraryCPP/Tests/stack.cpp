#include <iostream>
#include "stack.h"

int main()
{
    Stack* stack = stack_create();

    if (stack == nullptr)
    {
        std::cout << "Stack creation error\n";
        return 1;
    }

    if (!stack_empty(stack))
    {
        std::cout << "New stack should be empty\n";
        stack_delete(stack);
        return 1;
    }

    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);

    if (stack_empty(stack) || stack_get(stack) != 3)
    {
        std::cout << "Push error\n";
        stack_delete(stack);
        return 1;
    }

    stack_pop(stack);

    if (stack_get(stack) != 2)
    {
        std::cout << "Pop error\n";
        stack_delete(stack);
        return 1;
    }

    stack_pop(stack);
    stack_pop(stack);

    if (!stack_empty(stack))
    {
        std::cout << "Stack should be empty after pop\n";
        stack_delete(stack);
        return 1;
    }

    stack_push(stack, 4);

    if (stack_empty(stack) || stack_get(stack) != 4)
    {
        std::cout << "Push after empty error\n";
        stack_delete(stack);
        return 1;
    }

    stack_pop(stack);

    if (!stack_empty(stack))
    {
        std::cout << "Stack should be empty again\n";
        stack_delete(stack);
        return 1;
    }

    stack_delete(stack);

    std::cout << "Stack tests passed\n";
    return 0;
}