#include "beule.h"

static int pop_n(Stack* stack, Data* items, int count)
{
    int popped = 0;
    for (int i = 0; i < count; ++i)
    {
        if (stack_empty(stack)) break;
        items[i] = stack_get(stack);
        stack_pop(stack);
        popped++;
    }
    return popped;
}

void stack_dup(Stack* stack)
{
    if (!stack_empty(stack)) stack_push(stack, stack_get(stack));
}

void stack_drop(Stack* stack)
{
    if (!stack_empty(stack)) stack_pop(stack);
}

void stack_swap(Stack* stack)
{
    Data d[2];
    int n = pop_n(stack, d, 2);
    if (n == 2)
    {
        stack_push(stack, d[0]);
        stack_push(stack, d[1]);
    }
    else if (n == 1)
    {
        stack_push(stack, d[0]);
    }
}

void stack_over(Stack* stack)
{
    Data d[2];
    int n = pop_n(stack, d, 2);
    if (n == 2)
    {
        stack_push(stack, d[1]);
        stack_push(stack, d[0]);
        stack_push(stack, d[1]);
    }
    else if (n == 1)
    {
        stack_push(stack, d[0]);
    }
}

void stack_rot(Stack* stack)
{
    Data d[3];
    int n = pop_n(stack, d, 3);
    if (n == 3)
    {
        stack_push(stack, d[1]);
        stack_push(stack, d[0]);
        stack_push(stack, d[2]);
    }
    else
    {
        for (int i = n - 1; i >= 0; --i) stack_push(stack, d[i]);
    }
}