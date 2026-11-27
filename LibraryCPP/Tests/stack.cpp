#include <iostream>
#include "stack.h"

int main()
{
    Stack *stack = stack_create();

    if (!stack)
    {
        std::cout << "Stack creation error\n";
        return 1;
    }

    if (!stack_empty(stack))
    {
        std::cout << "New stack is not empty\n";
        stack_delete(stack);
        return 1;
    }

    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);

    if (stack_empty(stack))
    {
        std::cout << "Stack is empty after push\n";
        stack_delete(stack);
        return 1;
    }

    if (stack_get(stack) != 3)
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    stack_pop(stack);

    if (stack_get(stack) != 2)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    stack_pop(stack);

    if (stack_get(stack) != 1)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    stack_push(stack, 4);
    stack_push(stack, 5);

    if (stack_get(stack) != 5)
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    while (!stack_empty(stack))
        stack_pop(stack);

    if (!stack_empty(stack))
    {
        std::cout << "Stack is not empty\n";
        stack_delete(stack);
        return 1;
    }

    for (int i = 0 ; i < 1000 ; ++i)
        stack_push(stack, i);

    for (int i = 999 ; i >= 0 ; --i)
    {
        if (stack_empty(stack))
        {
            std::cout << "Stack became empty too early\n";
            stack_delete(stack);
            return 1;
        }

        if (stack_get(stack) != i)
        {
            std::cout << "Invalid stack order\n";
            stack_delete(stack);
            return 1;
        }

        stack_pop(stack);
    }

    if (!stack_empty(stack))
    {
        std::cout << "Stack is not empty after pops\n";
        stack_delete(stack);
        return 1;
    }

    stack_delete(stack);

    std::cout << "Stack tests passed\n";
    return 0;
}
