#include "stack.h"
#include "list.h"
#include <iostream>

struct Stack
{
    List* stackList;
};
Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->stackList = list_create();
    return stack;
}
void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    list_delete(stack->stackList);
    delete stack;
}
void stack_push(Stack *stack, Data data)
{
    list_insert(stack->stackList, data);
}
Data stack_get(const Stack *stack)
{
    return list_item_data(list_first(stack->stackList));
}
void stack_pop(Stack *stack)
{
    if (stack_empty(stack))
    {
        std::cout << "Error stack empty";
    }
    else
    {
        list_erase_top(stack->stackList);
        list_erase_first(stack->stackList);
    }
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->stackList) == nullptr;
}