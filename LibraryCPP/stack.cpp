#include "stack.h"
#include "list.h"

struct Stack{
    List* list = nullptr;
    ListItem* last_item = nullptr;
};

Stack *stack_create(){
    Stack* new_stack = new Stack;
    List* new_list = list_create();

    new_stack->list = new_list;

    return new_stack;
}

void stack_delete(Stack *stack){
    if (stack->list != nullptr)
        list_delete(stack->list);

    stack->list = nullptr;
    stack->last_item = nullptr;

    delete stack;
}

void stack_push(Stack *stack, Data data){
    stack->last_item = list_insert(stack->list, data);
}

Data stack_get(const Stack *stack){
    return list_item_data(stack->last_item);
}

void stack_pop(Stack *stack){
    if (stack->last_item != nullptr && list_item_prev(stack->last_item) != nullptr){
        stack->last_item = list_item_prev(stack->last_item);

        list_erase_next(stack->list, stack->last_item);
    }
    else if (stack->last_item != nullptr && list_item_prev(stack->last_item) == nullptr)
    {
        list_erase_first(stack->list);
        stack->last_item = nullptr;
    }
}

bool stack_empty(const Stack *stack){
    if (stack->last_item == nullptr)
        return true;
    else
        return false;
}
