#include "stack.h"
#include "list.h"

struct Stack
{
    List* list;
};

Stack* stack_create()
{
    Stack* stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack* stack)
{
    if (stack)
    {
        list_delete(stack->list);
        delete stack;
    }
}

void stack_push(Stack* stack, Data data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack)
{
    ListItem* first_item = list_first(stack->list);
    if (first_item)
        return list_item_data(first_item);
    else
        return (Data)0;
}

void stack_pop(Stack* stack)
{
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack)
{
    return list_first(stack->list) == nullptr;
}