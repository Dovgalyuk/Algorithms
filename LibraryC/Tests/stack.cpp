#include <iostream>
#include "stack.h"

void myfree(void *p)
{
    delete (int*)p;
}

int stack_get_int(Stack *s)
{
    void *v = stack_get(s);
    if (!v)
    {
        std::cout << "Invalid stack_get\n";
        stack_delete(s);
        exit(1);
    }
    return *(int*)v;
}

int main()
{
    Stack *stack = stack_create(myfree);

    stack_push(stack, new int(1));
    stack_push(stack, new int(2));
    stack_push(stack, new int(3));

    if (stack_get_int(stack) != 3)
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get_int(stack) << "\n";
    stack_pop(stack);

    if (stack_get_int(stack) != 2)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get_int(stack) << "\n";
    stack_pop(stack);

    if (stack_get_int(stack) != 1)
    {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get_int(stack) << "\n";
    stack_push(stack, new int(4));
    stack_push(stack, new int(5));

    if (stack_get_int(stack) != 5)
    {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    while (!stack_empty(stack))
    {
        std::cout << "Get: " << stack_get_int(stack) << "\n";
        stack_pop(stack);
    }

    stack_delete(stack);
}
