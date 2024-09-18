#include "stack.h"

struct Stack
{
    List* list = nullptr;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->list = list_create();

    return stack;
}

void stack_delete(Stack *stack)
{
    if(stack != nullptr)
        list_delete(stack->list);
}

void stack_push(Stack *stack, Data data)
{
    if(stack != nullptr)
        list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if(stack != nullptr)
        return list_item_data(list_first(stack->list));
    return (Data)0;
}

void stack_pop(Stack *stack)
{
    if(stack != nullptr)
        list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (stack != nullptr)
    {
        if (list_first(stack->list) == nullptr)
            return true;
        return false;
    }
    return true;
}
