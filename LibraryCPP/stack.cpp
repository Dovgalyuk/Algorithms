#include "stack.h"
#include "list.h"
#include <string>

struct Stack{
    List* list = nullptr;
    ListItem* last_item = nullptr;
};

Stack *stack_create(){
    Stack* new_stack = new Stack;

    new_stack->list = list_create();

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
    ListItem* first_item = list_first(stack->list);

    if (first_item != nullptr)
        return list_item_data(first_item);
    else
        return (Data)0;
}

void stack_pop(Stack *stack){
    stack->last_item = list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack){
    if (stack->last_item == nullptr)
        return true;
    else
        return false;
}
