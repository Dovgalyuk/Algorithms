#include "vector.h"

struct Vector
{
	Data* data; //указательнь на массив данных
	size_t size; //колличества элементов
	size_t capacity;//вместимость массива
};

Vector *vector_create()
{
    Vector* vector = new Vector; //выделение помяти под структуру
    vector->size = 0;// указываем что вектор пустой
	vector->capacity = 4; //начальная вместимость = 4 элемента
	vector->data = new Data[vector->capacity]; //выделяем память под массив
	return vector; //возвращаем указатель на созданный вектор
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
	delete[] vector->data;// освобождаем память  массива
	delete vector; // освобождаем память структуры
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];//возвращаем элемент по индекся
}

void vector_set(Vector *vector, size_t index, Data value)
{
	vector->data[index] = value; // присваиваем значение элементу по индексу
}

size_t vector_size(const Vector *vector)
{
    return vector->size;// возвращаем текущее количество элементов 
}

void vector_resize(Vector* vector, size_t size)// функция изменения размера вектора
{
	if (size > vector->capacity) {// если новый размер больше текущей вместимости

		while (vector->capacity < size) {// увеличиваем вместимость вектора вдвое пока она не станет больше

            vector->capacity *= 2;
        }
		Data* new_data = new Data[vector->capacity];// выделяем память под новый массив с увеличенной вместимостью

		for (size_t i = 0; i < vector->size; i++) { // проходит по старому массиву 

            new_data[i] = vector->data[i];// копирует данные в новый массив
        }

		delete[] vector->data; // освобождаем старый массив
        vector->data = new_data; // присваеваем новый массив 
    }
	vector->size = size; // обновляем текущее количество элементов
}
