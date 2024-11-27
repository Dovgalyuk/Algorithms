#include <stdlib.h>
#include <stdio.h>  
#include "stack.h"   

struct Stack  // Определение структуры Stack
{
    Vector *vector;  // Указатель на вектор, который будет использоваться для хранения элементов стека
    FFree* distruct; // Указатель на функцию distruct для освобождения данных
};

Stack *stack_create(FFree f)  // Функция для создания нового стека
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));  // Выделяем память под структуру стека
    if (!stack) {  // Проверяем, успешно ли выделена память
        fprintf(stderr, "Ошибка выделения памяти для стека\n");  
        return NULL;
    }
    stack->vector = vector_create(f);  // Создаем вектор с начальным размером 4 для стека
    if (!stack->vector) {  // Проверяем, успешно ли создан вектор
        free(stack);  // Освобождаем память под стек, если вектор не создан
        fprintf(stderr, "Ошибка выделения памяти для вектора в стеке\n");  
        return NULL;
    }
    stack->distruct = f; // Инициализация деструктора
    return stack;  // Возвращаем указатель на созданный стек
}

void stack_delete(Stack *stack)  // Функция для удаления стека и освобождения памяти
{
    if (!stack) {  // Проверяем, не равен ли указатель NULL
        return;  // Выход из функции, если стек пустой
    }

    while (!stack_empty(stack)) {  // Пока стек не пустой
        void *data = stack_pop(stack);  // Извлекаем верхний элемент стека
        if (data != NULL && stack->distruct) {  // Проверка на NULL и наличие функции деструктора
            stack->distruct(data);  // Освобождаем память, занятую данными
        }
    }
    vector_delete(stack->vector);  // Удаляем вектор, связанный со стеком
    free(stack);  // Освобождаем память, занятую самим стеком
}

void stack_push(Stack *stack, void *data)  // Функция для добавления элемента в стек
{
    if (!stack) {  // Проверяем, не равен ли указатель NULL
        fprintf(stderr, "Ошибка: стек не инициализирован\n");  
        return;  
    }
    push_back(stack->vector, data);  // Добавляем элемент в вектор, связанный со стеком
}

void *stack_get(const Stack *stack)  // Функция для получения верхнего элемента стека
{
    if (stack_empty(stack)) {  // Проверяем, не пуст ли стек
        fprintf(stderr, "Stack is empty!\n");  
        return NULL;  
    }
    return vector_get(stack->vector, vector_size(stack->vector) - 1);  // Возвращаем верхний элемент стека, используя вектор
}

void *stack_pop(Stack *stack)  // Функция для удаления верхнего элемента из стека
{
    if (stack_empty(stack)) {  // Проверяем, не пуст ли стек
        fprintf(stderr, "Stack underflow!\n");  
        return NULL;
    }
    return pop_back(stack->vector);  // Удаляем верхний элемент из вектора, связанного со стеком
}

bool stack_empty(const Stack *stack)  // Функция для проверки, пуст ли стек
{
    return vector_size(stack->vector) == 0;  // Возвращаем true, если размер вектора равен 0
}
