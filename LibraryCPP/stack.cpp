#include <memory>
#include <stdexcept>
#include "list.h"
#include "stack.h"

struct Stack
{
    std::unique_ptr<List, decltype(&list_delete)> list{list_create(), list_delete};
};

Stack *stack_create()
{
    return new Stack;
}

void stack_delete(Stack *stack)
{
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->list.get(), data);
}

Data stack_get(const Stack *stack)
{
    if (stack_empty(stack))
        throw std::out_of_range("Empty stack");
    return list_item_data(list_first(stack->list.get()));
}

void stack_pop(Stack *stack)
{
    if (stack_empty(stack))
        throw std::out_of_range("Empty stack");
    list_erase_first(stack->list.get());
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list.get()) == nullptr;
}
