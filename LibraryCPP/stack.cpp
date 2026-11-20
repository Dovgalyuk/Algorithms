#include "stack.h"
#include "list.h"

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
    if (stack != nullptr)
    {
        list_delete(stack->list);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data)
{
    if (stack != nullptr && stack->list != nullptr) list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if (stack == nullptr || stack->list == nullptr) return (Data)0;

    ListItem* item = list_first(stack->list);
    if (item == nullptr) return (Data)0;

    return list_item_data(item);
}

void stack_pop(Stack *stack)
{
    if (stack != nullptr && stack->list != nullptr) list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (stack == nullptr || stack->list == nullptr) return true;

    return list_first(stack->list) == nullptr;
}
