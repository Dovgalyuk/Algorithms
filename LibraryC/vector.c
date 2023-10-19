#include <stdlib.h>
#include "vector.h"

typedef struct Vector
{
	size_t size;
	Data* v;
	ffree* deleter;
} Vector;

Vector* vector_create(ffree f)
{
	Vector* newvector = (Vector*)malloc(sizeof(Vector));
	newvector->size = 0;
	newvector->v = NULL;
	newvector->deleter = f;
	return newvector;
}

void vector_delete(Vector* vector)
{
	if (vector != NULL) {
		if (vector->deleter != NULL)
			for (size_t i = 0; i < vector->size;i++) {
				vector->deleter(vector->v[i]);
			}
		else
			for (size_t i = 0; i < vector->size;i++) {
				free(vector->v[i]);
			}
		free(vector->v);
		free(vector);
	}
}

Data vector_get(const Vector* vector, size_t index)
{
	if (vector != NULL)
		if (index < vector->size)
			return vector->v[index];
	return (Data)0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
	if ((vector != NULL) && (index < vector->size))
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
	if (vector != NULL)
		return vector->size;
	return 0;
}

void vector_resize(Vector* vector, size_t size)
{
	if (vector != NULL) {
		if (size > vector->size) {
			vector->v = (Data*)realloc(vector->v, size * sizeof(Data));
			for (size_t i = vector->size;i < size;i++) {
				Data a = (Data)malloc(sizeof(Data));
				vector->v[i] = a;
			}
			vector->size = size;
		}
		else if (size < vector->size) {
			for (size_t i = size;i < vector->size;i++) {
				if (vector->v[i] != NULL) {
					if (vector->deleter != NULL)
						vector->deleter(vector->v[i]);
					else
						free(vector->v[i]);
				}
			}
			vector->size = size;
		}
	}
}
