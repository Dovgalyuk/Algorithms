#include "stack.h"
#include "list.h"

struct Stack
{
    List* list;
};

Stack *stack_create()
{
    return new Stack{ list_create() };
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
    if(stack_empty(stack)){
        return (Data)0;
    }
    else{
        return list_item_data(list_first(stack->list));
    }
    
}

void stack_pop(Stack *stack)
{
    if(stack_empty(stack)){
        return;
    }
    else{
        list_erase_first(stack->list);
    }
}

bool stack_empty(const Stack *stack)
{
    if(list_first(stack->list) == nullptr){
        return true;
    }
    else{
        return false;
    }
}
