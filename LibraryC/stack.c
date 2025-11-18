#include <stdlib.h>
#include "stack.h"

typedef struct Stack {
    Data d;
} Stack;

Stack* stack_create(FFree f)
{
    (void)f;
    return malloc(sizeof(Stack));
}

void stack_delete(Stack* stack)
{
    (void)stack;
    free(stack);
}

void stack_push(Stack* stack, Data data)
{
    (void)stack;
    (void)data;
}

Data stack_get(const Stack* stack)
{
    (void)stack;
    return 0;
}

void stack_pop(Stack* stack)
{
    (void)stack;
}

bool stack_empty(const Stack* stack)
{
    (void)stack;
    return true;
}
