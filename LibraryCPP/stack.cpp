#include "./stack.h"

struct Stack
{
    List * list;
};

Stack *stack_create()
{
    Stack * stack = new Stack();
    stack->list = list_create();
    return new Stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (stack->list == nullptr){
        return true;
    }
    else return false;
}
