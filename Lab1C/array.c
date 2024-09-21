#include "array.h"  // Подключение заголовочного файла
#include <stdlib.h> 

typedef struct Array 
{
  size_t size; // размер типа size_t 
  Data* data;  //  поле data  типа void*
} Array;  


// create array
Array *array_create(size_t size, FFree f) 
{
  Array* arr = malloc(sizeof(Array)); //  Выделяем память для структуры 

  if (arr == NULL) { // если ошибка выделения памяти завершаем операцию 
    return NULL;
  }
  arr -> data = malloc(size * sizeof(Data));   // выделяем память для массива 
  if (arr -> data == NULL) {  // если память не выделилась освобождаем память для структуры и возвращаем NULL
    free(arr);
    return NULL;
  }

  arr -> size = size; // Присваиваем полю size  значение переменной size
  return arr;// возвращаем указатель на созданный массив 
}

// delete array, free memory
void array_delete(Array *arr) 
{
  if (arr != NULL) { // если массив не пустой то 
      free(arr -> data); // освобождаем память занятую элементами массива 
      arr -> data = NULL; 
      free(arr);     // освобождаем память занятую структурой  
  }
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
