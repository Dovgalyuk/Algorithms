#include "stack.h"
#include "list.h"
#include <iostream>

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
    if (stack) {
        list_delete(stack->list);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data)
{
    if (stack) {
        list_insert(stack->list, data);
    }
    else {
        std::cerr << "Error: stack_push called with null stack" << std::endl;
    }
}

Data stack_get(const Stack *stack)
{
    if (stack && !stack_empty(stack)) {
        ListItem* first = list_first(stack->list);
        return list_item_data(first);
    }
    else {
        std::cerr << "Error: stack_get called on null or empty stack" << std::endl;
        return 0;
    }
}

void stack_pop(Stack *stack)
{
    if (stack && !stack_empty(stack)) {
        list_erase_first(stack->list);
    }
    else {
        std::cerr << "Error: stack_pop called on null or empty stack" << std::endl;
    }
}

bool stack_empty(const Stack *stack)
{
    if (stack) {
        return list_first(stack->list) == nullptr;
    }
    else {
        return true;
    }
}
