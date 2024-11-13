#include "stack.h"
#include "list.h"
#include "list.cpp"

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if (list_first(stack->list) == nullptr) return (Data)0;
    return list_first(stack->list)->data;
}

void stack_pop(Stack *stack)
{
    if (list_first(stack->list) != nullptr) 
        list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list)->data;
}
