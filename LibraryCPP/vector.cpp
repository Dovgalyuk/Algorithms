#include "vector.h"

struct Vector
{
	Data* data;
	size_t size;
	size_t capacity;
	size_t size_max;

	Vector() {
		size = 1;
		size_max = 2;
		data = new Data[size_max];
	}
};

Vector* vector_create()
{
	Vector* vector = new Vector;
	vector->data = nullptr;
	vector->size = 0;
	vector->capacity = 0;
	return vector;
   // return new Vector(size);
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
	delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
	if (index < vector->size)
	{
		return vector->data[index];
	}
	return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
	//size_t size = vector_size(vector);
	if (index < vector->size)
		vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
	//if (vector != nullptr) {
	//	return vector->size;
	//}
	//else {
	//	// обработка случая, когда arr равен nullptr
	//	return 0; // или другое подходящее значение по умолчанию
	//}
	return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
	/*if (size <= vector->capacity)
	{
		vector->size = size;
	}
	else
	{
		Data* new_data = new Data[size];
		for (size_t i = 0; i < vector->size; i++)
		{
			new_data[i] = vector->data[i];
		}
		delete[] vector->data;
		vector->data = new_data;
		vector->size = size;
		vector->capacity = size;
	}*/
	if (size <= vector->size_max) {
		vector->size = size;
		return;
	}
	size_t size_new_max = size * 2;
	Data* current = new Data[size_new_max];
	for (int i = 0; i < (int)vector->size; i++) {
		current[i] = vector->data[i];
	}
}
