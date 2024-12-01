#include "stack.h"
#include "list.h"

struct Stack {
    List *list = nullptr;
};


Stack *stack_create() {
    Stack *stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack *stack) {
    if (stack->list!=nullptr){
        list_delete(stack->list);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data) {
    if (stack != nullptr) {
        list_insert(stack->list, data); 
    }
}

Data stack_get(const Stack *stack) {
    if(stack != nullptr){
        ListItem *item = list_first(stack->list);
        if(item != nullptr){
            return list_item_data(item);
        }
    }
    return Data();
}

void stack_pop(Stack *stack) {
    if (stack != nullptr) {
        list_erase_first(stack->list);
    }
}

bool stack_empty(const Stack *stack) {
    return (stack == nullptr) || (list_first(stack->list) == nullptr);
}
