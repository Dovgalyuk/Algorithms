#include "stack.h"
#include "list.h"
#include <stdlib.h>
struct Stack
{
    List* l = nullptr;
};

Stack *stack_create()
{
    Stack* stack  = new Stack;
    stack->l = list_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->l);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->l,data);
}

Data stack_get(const Stack *stack)
{
    return list_item_data(list_first(stack->l));
}

void stack_pop(Stack *stack)
{
    list_erase_first(stack->l);
}

bool stack_empty(const Stack *stack)
{
    if (list_first(stack->l) == nullptr) {
        return true;
    }
    else return false;
    
}
