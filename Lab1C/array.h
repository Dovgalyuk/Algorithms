#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdint.h>

typedef int* Data; // Псевдоним на тип void * 
typedef void (*FFree)(void*); // Псевдоним для функции типа void с аргументом void* 

typedef struct Array Array;  // Псевдоним Array для структуры array

#ifdef __cplusplus /* Как я понял данный код блока нужен для связки плюсов и си т.к 
 у них разные вызовы функций*/
extern "C" {
#endif // Подробнее узнать о соглашении о вызовах 

Array* array_create(size_t size, FFree f);
void array_delete(Array *arr);
Data array_get(const Array *arr, size_t index);
int array_set(Array *arr, size_t index, Data value);
size_t array_size(const Array *arr);

#ifdef __cplusplus
}
#endif

#endif
