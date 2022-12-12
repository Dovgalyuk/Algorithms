#include "stack.h"
#include "list.h"
#include <cstddef>

struct Stack
{
    List *list;

    Stack() {
        this->list = list_create();
    }

    ~Stack() {
        list_delete(this->list);
    }
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
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if(list_first(stack->list) == nullptr)
        throw "No elements in stack";

    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
    if(list_first(stack->list) == nullptr)
        throw "Popping empty element";

    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list) == nullptr;
}
