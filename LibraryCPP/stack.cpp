#include "list.h"
#include <string>

struct Stack
{
    List *list;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, const std::string& data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    ListItem *item = list_first(stack->list);
    if (item != nullptr)
        return list_item_data(item);
    else
        return (Data)0;
}

void stack_pop(Stack *stack)
{
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list) == nullptr;
}