#include "stack.h"
#include "list.h"
#include <stdexcept>

struct Stack
{
    List* list = nullptr;
};

Stack* stack_create()
{
    Stack* pointer = new Stack;
    pointer->list = list_create();
    return pointer;
}

void stack_delete(Stack* stack)
{
    if (!stack) {
        throw std::invalid_argument("Stack nullptr");
    }
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    if (!stack) {
        throw std::invalid_argument("Stack nullptr");
    }
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack)
{
    if (!stack) {
        throw std::invalid_argument("Stack nullptr");
    }
    if (stack_empty(stack)) {
        throw std::invalid_argument("Stack empty");
    }

    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack* stack)
{
    if (!stack) {
        throw std::invalid_argument("Stack nullptr");
    }
    if (stack_empty(stack)) {
        throw std::invalid_argument("Stack empty");
    }
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack)
{
    if (!stack) {
        throw std::invalid_argument("Stack nullptr");
    }
    return (list_first(stack->list) == nullptr);
}
