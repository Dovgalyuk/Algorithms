#include "stack.h"
#include "vector.h"

struct Stack {
    Vector* vector;
};

// Создание нового стека
Stack* stack_create() {
    Stack* stack = new Stack;
    stack->vector = vector_create(); 
    return stack;
}

// Удаление стека и освобождение памяти
void stack_delete(Stack* stack) {
    vector_delete(stack->vector);
    delete stack; 
}

// Добавление элемента в стек
void stack_push(Stack* stack, Data data) {
    size_t size = vector_size(stack->vector); // Получение текущего размера вектора
    vector_resize(stack->vector, size + 1);   // Увеличение размера вектора
    vector_set(stack->vector, size, data);    // Установка нового элемента на вершину стека
}

// Получение элемента с вершины стека (без удаления)
Data stack_get(const Stack* stack) {
    size_t size = vector_size(stack->vector); // Получение текущего размера вектора
    if (size > 0) {
        return vector_get(stack->vector, size - 1); // Возвращаем последний элемен т
    }
    return 0; // Если стек пуст, возвращаем 0 
}

// Удаление элемента с вершины стека
void stack_pop(Stack* stack) {
    size_t size = vector_size(stack->vector); // Получение текущего размера вектора
    if (size > 0) {
        vector_resize(stack->vector, size - 1); // Уменьшить размер масива
    }
}

// Проверка, пуст ли стек
bool stack_empty(const Stack* stack) {
    return vector_size(stack->vector) == 0; // Если размер вектора 0, то значит стек пуст
}

// Получение размера стека
size_t stack_size(const Stack* stack) {
    return vector_size(stack->vector); // Возвращаем размер вектора
}
