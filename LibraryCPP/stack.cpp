#include "stack.h"

// Создание пустого стека
Stack* stack_create() {
    Stack* stack = new Stack;
    stack->list = list_create();
    return stack;
}

// Удаление стека
void stack_delete(Stack* stack) {
    list_delete(stack->list);
    delete stack;
}

// Добавление элемента в стек
void stack_push(Stack* stack, Data data) {
    list_insert(stack->list, data);
}

// Получение верхнего элемента стека
Data stack_get(const Stack* stack) {
    ListItem* first = list_first(stack->list);
    if (first == nullptr) {
        return 0; 
    }
    return list_item_data(first);
}

// Удаление верхнего элемента стека
void stack_pop(Stack* stack) {
    list_erase_first(stack->list);
}

// Проверка, пуст ли стек
bool stack_empty(const Stack* stack) {
    return list_first(stack->list) == nullptr;
}