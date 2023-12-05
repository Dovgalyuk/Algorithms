#include <stdlib.h>
#include "vector.h"


typedef struct Vector
{
	size_t size;
	size_t maxsize;
	Data* v;
	ffree* deleter;
} Vector;

Vector* vector_create(ffree f)
{
	Vector* newvector = (Vector*)malloc(sizeof(Vector));
	newvector->size = 0;
	newvector->maxsize = 0;
	newvector->v = NULL;
	newvector->deleter = f;
	return newvector;
}

void vector_delete(Vector* vector)
{
	if (vector) {
		if (vector->deleter)
			for (size_t i = 0; i < vector->maxsize; i++) {
				vector->deleter(vector->v[i]);
			}
		else
			for (size_t i = 0; i < vector->maxsize; i++) {
				free(vector->v[i]);
			}
		free(vector->v);
		free(vector);
	}
}

int vector_get(const Vector* vector, size_t index)
{
	if (vector)
		if (index < vector->size)
			return vector->v[index];
	return (Data)0;
}

int vector_set(Vector* vector, size_t index, Data value)
{
	if ((vector) && (index < vector->size))
		if (vector->v[index] != NULL) {
			if (vector->deleter != NULL)
				vector->deleter(vector->v[index]);
			else
				free(vector->v[index]);
		}
	vector->v[index] = value;
}

size_t vector_size(const Vector* vector)
{
	if (vector)
		return vector->size;
	return 0;
}

void vector_resize(Vector* vector, size_t size)
{
	if (vector != NULL) {
		if (size > vector->size) {
			if (vector->maxsize < size)
			{
				vector->v = (Data*)realloc(vector->v, 3 * size * sizeof(Data));
				for (size_t i = vector->maxsize; i < 3 * size; i++)
					vector->v[i] = NULL;
				vector->maxsize = 3 * size;
			}
			vector->size = size;
		}
		else if (size < vector->size) {
			vector->size = size;
		}
	}
}