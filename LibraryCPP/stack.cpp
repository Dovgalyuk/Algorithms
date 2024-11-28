#include "stack.h"
#include "list.h"

struct Stack {
    List *list = nullptr;
    ListItem *last = nullptr;
};


Stack *stack_create() {
    Stack *stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack *stack) {
    if (stack->list!=nullptr){
        list_delete(stack->list);
        stack->list = nullptr;
        stack->last = nullptr;
        delete stack;
    }
}

void stack_push(Stack *stack, Data data) {
    stack->last = list_insert(stack->list, data);
}

Data stack_get(const Stack *stack) {
    ListItem *item = stack->last;
    if (item != nullptr) {
        return list_item_data(item);
    } else {
        return (Data)0;
    }
}

void stack_pop(Stack *stack) {
    if (stack->last != nullptr) {
        stack->last = list_erase_first(stack->list);
    }
}

bool stack_empty(const Stack *stack) {
    return stack->last == nullptr;
}
