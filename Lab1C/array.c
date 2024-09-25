#include "array.h"  // Подключение заголовочного файла
#include <stdlib.h> 

typedef struct Array 
{
  size_t size; // размер типа size_t 
  Data *data;  //  поле data  типа int*
  FFree *distruct;
} Array;  


// create array
Array *array_create(size_t size, FFree field) 
{
    Array *arr = malloc(sizeof(Array)); // Выделяем память для структуры

    if (arr == NULL) { // Если ошибка выделения памяти, завершаем операцию
        return NULL;
    }

    arr -> data = malloc(size * sizeof(Data)); // Выделяем память для массива
    if (arr -> data == NULL) { // Если память не выделилась, освобождаем память для структуры и возвращаем NULL
        free(arr);
        return NULL;
    }

    arr -> distruct = field;
    arr -> size = size; // Присваиваем полю size значение переменной size
    return arr; // Возвращаем указатель на созданный массив
}

// delete array, free memory
void array_delete(Array *arr) 
{
    if (arr == NULL) {
        return;
    }

    if (arr -> distruct != NULL) {
        for (size_t i = 0; i < arr -> size; i++) {
            free(arr -> data[i]);
        }
    }
    free(arr -> data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index) // тип const указывает на то что данные функция изменять не будет
{
    return arr -> data[index]; // возвращаем элемент по указанному индексу 
}

// sets the specified array element to the value
int array_set(Array *arr, size_t index, Data value) 
{
  if (arr == NULL || index >= arr->size) { // Если  массив пуст или размер меньше указанного индекса мы все плохо
    return -1;
  }
  arr -> data[index] = value;// а иначе присваиваем указанному индексу указанное значение
  return 0;
}

// returns array size
size_t array_size(const Array *arr) 
{
    return arr -> size; // просто  возвращаем размер 
}


/*void array_free_elements(Array* arr) {
    if (arr == NULL) {
        return;
    }

    for (size_t i = 0; i < arr -> size; ++i) {
        free(array_get(arr, i));
    }
}*/
