#include "stack.h"
#include "list.h"

struct Stack
{
    List* list;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    ListItem* item = list_item_prev(list_first(stack->list));
    if (item) {
        return list_item_data(item);
    }
    return (Data)0; // Или какое-то значение по умолчанию
}

void stack_pop(Stack *stack)
{
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list) == nullptr;
}
