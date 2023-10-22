#include <stdlib.h>
#include "vector.h"

typedef struct Vector
{
	size_t size;
	size_t maxsize;
	Data* vector;
	FFree* deleter;
} Vector;

Vector* vector_create(FFree f)
{
	Vector* newvector = (Vector*)malloc(sizeof(Vector));
	newvector->size = 0;
	newvector->maxsize = 0;
	newvector->vector = NULL;
	newvector->deleter = f;
	return newvector;
}

void vector_delete(Vector* vector)
{
	if (vector) {
		if (vector->deleter)
			for (size_t i = 0; i < vector->maxsize; i++) {
				vector->deleter(vector->vector[i]);
			}
		else
			for (size_t i = 0; i < vector->maxsize; i++) {
				free(vector->vector[i]);
			}
		free(vector->vector);
		free(vector);
	}
}

Data vector_get(const Vector* vector, size_t index)
{
	if (vector)
		if (index < vector->size)
			return vector->vector[index];
	return (Data)0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
	if ((vector) && (index < vector->size))
		if (vector->vector[index]) {
			if (vector->deleter)
				vector->deleter(vector->vector[index]);
			else
				free(vector->vector[index]);
		}
	vector->vector[index] = value;
}

size_t vector_size(const Vector* vector)
{
	if (vector)
		return vector->size;
	return 0;
}

void vector_resize(Vector* vector, size_t size)
{
	if (vector) {
		if (size > vector->size) {
			if (vector->maxsize < size)
			{
				vector->vector = (Data*)realloc(vector->vector, size * sizeof(Data));
				for (size_t i = vector->maxsize; i < size; i++)
					vector->vector[i] = NULL;
				vector->maxsize = size;
			}
			vector->size = size;
		}
		else if (size < vector->size) {
			for (size_t i = 2 * size; i < vector->maxsize; i++) {
				if (vector->vector[i]) {
					if (vector->deleter)
						vector->deleter(vector->vector[i]);
					else
						free(vector->vector[i]);
				}
			}
			vector->size = size;
			vector->maxsize = size;
		}
	}
}
