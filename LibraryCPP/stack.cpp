#include "stack.h"
#include "list.h"

struct Stack
{
    List* list;
    Stack()
    {
        list = list_create();
        list_insert(list, 'a');
    }
};

Stack* stack_create()
{
    return new Stack();
}

void stack_delete(Stack* stack)
{
    // TODO: free stack elements
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    list_insert_after(stack->list, list_first(stack->list), data);
}

Data stack_get(const Stack* stack)
{
    Data n;
    n = list_item_data(list_item_next(list_first(stack->list)));
    return (n);
}

void stack_pop(Stack* stack)
{
    list_erase_next(stack->list, list_first(stack->list));
}

bool stack_empty(const Stack* stack)
{
    if (list_item_next(list_first(stack->list)) == nullptr)
        return true;
    else
        return false;
}
