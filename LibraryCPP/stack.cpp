#include "stack.h"
#include "list.h"

struct Stack {
    List* list; // Внутренний односвязный список для хранения элементов стека
};

// Создание нового стека
Stack* stack_create() {
    Stack* stack = new Stack;
    stack->list = list_create(); // Инициализация списка
    return stack;
}

// Удаление стека и освобождение памяти
void stack_delete(Stack* stack) {
    list_delete(stack->list); // Удаление списка
    delete stack; // Удаление структуры стека
}

// Добавление элемента в стек
void stack_push(Stack* stack, Data data) {
    list_insert(stack->list, data); // Вставляем элемент в начало списка (как вершину стека)
}

// Получение элемента с вершины стека (без удаления)
Data stack_get(const Stack* stack) {
    ListItem* first = list_first(stack->list); // Получаем первый элемент списка (вершину стека)
    if (first != nullptr) {
        return list_item_data(first); // Возвращаем данные из первого элемента
    }
    return 0; // Если стек пуст, возвращаем 0 (или другое значение по умолчанию)
}

// Удаление элемента с вершины стека
void stack_pop(Stack* stack) {
    if (list_first(stack->list) != nullptr) {
        list_erase_first(stack->list); // Удаляем первый элемент списка (вершину стека)
    }
}

// Проверка, пуст ли стек
bool stack_empty(const Stack* stack) {
    return list_first(stack->list) == nullptr; // Если нет первого элемента, значит стек пуст
}

// Получение размера стека
size_t stack_size(const Stack* stack) {
    size_t size = 0;
    for (ListItem* item = list_first(stack->list); item != nullptr; item = list_item_next(item)) {
        size++; // Подсчитываем количество элементов в списке (размер стека)
    }
    return size;
}
