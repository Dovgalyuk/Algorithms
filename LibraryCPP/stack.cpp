#include "stack.h"
#include "list.h"
#include <stdexcept>

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
    if (!stack) return;
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    if (!stack) return;
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if (!stack || !stack->list) {
        throw std::runtime_error("Stack is empty");
    }
    ListItem* first = list_first(stack->list);
    if (!first) {
        throw std::runtime_error("Stack is empty");
    }
    return list_item_data(first);
}

void stack_pop(Stack *stack)
{
    if (!stack || !stack->list) return;
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (!stack || !stack->list) return true;
    return list_first(stack->list) == nullptr;
}