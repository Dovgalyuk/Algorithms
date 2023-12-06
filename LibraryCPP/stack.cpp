#include "stack.h"
#include "list.h"

struct Stack
{
    List* list;
};

Stack *stack_create()
{
    Stack* temp = new Stack;
    temp->list = list_create();
    return temp;
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
    ListItem* first = list_first(stack->list);
    if (first)
    {
        return list_item_data(first);
    }
    return (Data)0; // Assuming default value is 0
}

void stack_pop(Stack *stack)
{
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list) == NULL;
}