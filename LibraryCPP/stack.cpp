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
    if(list_first(stack->list) == nullptr) {
        throw "Error: not enough elements!";
    } else {
        return list_item_data(list_first(stack->list));
    }
}

void stack_pop(Stack *stack)
{
    if (list_first(stack->list) == nullptr) {
        throw "Error: deleting an empty element!";
    } else {
        list_erase_head(stack->list);
    }
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list) == nullptr;
}