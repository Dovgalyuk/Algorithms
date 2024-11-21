#include "stack.h"
#include "list.h"
#include <stdexcept>


struct Stack {
    List* list; 
};

Stack* stack_create() {
    Stack* stack = new Stack;
    stack->list = list_create(); 
    return stack;
}

void stack_delete(Stack* stack) {
    list_delete(stack->list); 
    delete stack; 
}

void stack_push(Stack* stack, Data data) {
    list_insert(stack->list, data); 
}

Data stack_get(const Stack* stack) {
    if (stack_empty(stack)) {
        throw std::runtime_error("Stack is empty");
    }
    ListItem* item = list_last(stack->list); // Получаем последний элемент списка
    return list_item_data(item); // Возвращаем данные верхнего элемента
}

void stack_pop(Stack* stack) {
    if (stack_empty(stack)) {
        throw std::runtime_error("Stack is empty"); // Генерируем ошибку, если стек пуст
    }
    list_erase_last(stack->list); // Удаляем последний элемент списка
}

bool stack_empty(const Stack* stack) {
    return list_first(stack->list) == nullptr; // Проверяем, есть ли элементы в списке
}
