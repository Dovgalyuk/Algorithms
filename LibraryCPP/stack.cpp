#include "stack.h"
#include "list.h"

struct Stack
{
    List* list;
};

Stack *stack_create()
{
    return new Stack{ list_create() };
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    if (!stack) return;
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    if (stack)
    {
        list_insert(stack->list, data);
    }
}

Data stack_get(const Stack *stack)
{
    if (!stack || stack_empty(stack)) return (Data)0;
    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
    if (!stack || stack_empty(stack)) return;
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (stack && list_first(stack->list) != nullptr)
    {
        return false;
    }
    return true;
}
