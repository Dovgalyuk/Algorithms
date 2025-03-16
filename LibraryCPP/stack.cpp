#include "stack.h"

struct Stack
{
    List *list;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    if (stack) {
        stack->list = list_create();
    }
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
    if (stack && stack->list) {
        list_insert(stack->list, data); 
    }
}

Data stack_get(const Stack *stack)
{
    if (stack && stack->list) {
        ListItem *first = list_first(stack->list);
        if (first) {
            return list_item_data(first);
        }
    }
    return (Data)0;
}

void stack_pop(Stack *stack)
{
    if (stack && stack->list) {
        ListItem *first = list_erase_first(stack->list);
        if(first){
            delete first; 
        }
    }
}

bool stack_empty(const Stack *stack)
{
    if (stack && stack->list) {
        return list_first(stack->list) == nullptr;
    }
    return true;
}
