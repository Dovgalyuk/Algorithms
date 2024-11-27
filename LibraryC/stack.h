#ifndef STACK_H  // Защита от повторного определения заголовка
#define STACK_H

#include <stdbool.h>  
#include "vector.h"   

#ifdef __cplusplus
extern "C" {  // Если используется C++, оборачиваем в код C
#endif

typedef struct Stack Stack;  // Определяем тип Stack как указатель на структуру Stack

Stack *stack_create();  // Объявление функции для создания нового стека

void stack_delete(Stack *stack);  // Объявление функции для удаления стека и освобождения памяти

void stack_push(Stack *stack, void *data);  // Объявление функции для добавления элемента в стек

void *stack_get(const Stack *stack);  // Объявление функции для получения верхнего элемента стека

void *stack_pop(Stack *stack);  // Объявление функции для удаления верхнего элемента стека

bool stack_empty(const Stack *stack);  // Объявление функции для проверки, пуст ли стек

#ifdef __cplusplus
}  // Закрываем блок C для C++
#endif

#endif
