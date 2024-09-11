#include "stack.h"
#include "list.h"
#include <stdexcept>


struct Stack
{
    List *list = nullptr;
};

Stack *stack_create()
{
    Stack *ptr = new Stack;
    ptr->list = list_create();
    return ptr;
}

void stack_delete(Stack *stack)
{
    if (!stack) throw std::invalid_argument("The stack pointer is nullptr");

    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    if (!stack) throw std::invalid_argument("The stack pointer is nullptr");
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if (!stack) throw std::invalid_argument("The stack pointer is nullptr");
    if (stack_empty(stack)) throw std::invalid_argument("The stack is empty");
    
    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
    if (!stack) throw std::invalid_argument("The stack pointer is nullptr");
    if (stack_empty(stack)) throw std::invalid_argument("The stack is empty");
    
    if (list_erase_first(stack->list)) return; //This construction is necessary to prevent the compiler from issuing an error about an ignored return value
}

bool stack_empty(const Stack *stack)
{
    if (!stack) throw std::invalid_argument("The stack pointer is nullptr");
    return (list_first(stack->list) == nullptr);
}
