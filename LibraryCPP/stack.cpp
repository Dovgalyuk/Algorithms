#include "stack.h"
#include "list.h"

struct Stack
{
    List* stack;
    Stack()
    {
        stack = list_create();
    }
};

Stack* stack_create()
{
    return new Stack;
}

void stack_delete(Stack* stack)
{
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    list_insert(stack->stack, data);
}

Data stack_get(const Stack* stack)
{
    return list_item_data(list_first(stack->stack));
}

void stack_pop(Stack* stack)
{
    if (stack_empty(stack) == false)
    {
        ListItem* second_element = list_item_next(list_first(stack->stack));
        delete list_first(stack->stack);
        stack->stack->head = second_element;

    }
}

bool stack_empty(const Stack* stack)
{
    if (list_first(stack->stack) == nullptr)
        return true;
    else
        return false;
}
