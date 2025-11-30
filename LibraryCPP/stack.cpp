#include "stack.h"
#include "list.h"

struct Stack
{
    List* list;
};

Stack *stack_create()
{
    Stack* st = new Stack;
    st->list = list_create();
    return st;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert_after(stack->list, stack->list->tail, data);
}

Data stack_get(const Stack *stack)
{
return stack->list->tail->value;
}

void stack_pop(Stack *stack)
{
    ListItem* last = stack->list->tail;
    if (last == nullptr)
        return;

    if (last->prev) {
        stack->list->tail = last->prev;
        last->prev->next = nullptr;
    } else {
        stack->list->head = nullptr;
        stack->list->tail = nullptr;
    }

    delete last;
}

bool stack_empty(const Stack *stack)
{
    return stack->list->head == nullptr;
}
