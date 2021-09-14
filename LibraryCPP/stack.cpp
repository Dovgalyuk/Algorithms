#include "stack.h"
#include "list.cpp"

struct Stack
{
    List* list = nullptr;
    ListItem* last = nullptr;

    Stack() {
        list = list_create();
    }
};

Stack *stack_create()
{
    return new Stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    if (!list_first(stack->list)) {
        stack->last = list_insert(stack->list, data);
    } else {
        stack->last = list_insert_after(stack->list, stack->last, data);
    }
}

Data stack_get(const Stack *stack)
{
    return list_item_data(stack->last);
}

void stack_pop(Stack *stack)
{
    list_erase(stack->list, stack->last);
    stack->last = stack->last->prev;
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list);
}
