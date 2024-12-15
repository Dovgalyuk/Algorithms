#ifndef STACK_H
#define STACK_H

#include <cstddef>  // Для типа size_t

// Объявление типа Data
typedef size_t Data;  // Тип данных для стека

// Структура стека
struct Stack;

// Создание пустого стека
Stack* stack_create();

// Удаление стека
void stack_delete(Stack* stack);

// Добавление данных в стек (O(1) в среднем)
void stack_push(Stack* stack, Data data);

// Получение последнего элемента стека
Data stack_get(const Stack* stack);

// Удаление последнего элемента стека (O(1))
void stack_pop(Stack* stack);

// Проверка, пуст ли стек
bool stack_empty(const Stack* stack);

#endif
