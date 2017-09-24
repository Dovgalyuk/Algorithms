#include <stdlib.h>
#include "vector.h"




struct Vector
{
	int *Element = new int[0];
	size_t size = 0;
};

// �������� �������
Vector *vector_create()
{
	Vector *NewVector = new Vector;
	return NewVector;
}

// �������� �������
void vector_delete(Vector *vector)
{
	delete  vector;
}

// �������� �������� ������� �������
int vector_get(Vector *vector, size_t index)
{
	return vector->Element[index];
}

// ���������� �������� ������� �������
void vector_set(Vector *vector, size_t index, int value)
{
	vector->Element[index] = value;
}

// �������� ������� ������ �������
size_t vector_size(Vector *vector)
{
	return vector->size;
}

// �������� ������ �������
void vector_resize(Vector *vector, size_t size)
{
	int *buffer = new int[size];
	vector->size = size;
	for (int i = 0; i < size; i++)
		buffer[i] = vector->Element[i];
	delete[] vector->Element;
	vector->Element = buffer;


}

