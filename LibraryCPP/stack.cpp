#include "stack.h"
#include "list.h"

struct Stack {
    List* list;
    Stack() {
        list = list_create();
    }
    
    ~Stack(){
        list_delete(list);
    }
};

Stack* stack_create() {
    return new Stack;
}


void stack_delete(Stack* stack) {
    delete stack;
}

void stack_push(Stack* stack, Data data) {
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack) {
    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack* stack) {
    list_erase(stack->list, list_first(stack->list));
}

bool stack_empty(const Stack* stack) {
    if (list_first(stack->list) == nullptr) return true;
    else return false;
}
