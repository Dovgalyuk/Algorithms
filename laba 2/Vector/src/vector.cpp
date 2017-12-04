#include <stdlib.h>
#include "vector.h"

struct Vector {
	int *mass;
	size_t size;
};

// �������� �������
Vector *vector_create() {
	Vector *vector = new Vector;
	vector->mass = new int[0];
	vector->size = 0;
	return vector;
}

// �������� �������
void vector_delete(Vector *vector) {
	delete [] vector->mass;
	delete vector;
}

// �������� �������� ������� �������
int vector_get(Vector *vector, size_t index) {
	return vector->mass[index];
}

// ���������� �������� ������� �������
void vector_set(Vector *vector, size_t index, int value) {
	vector->mass[index] = value;
}

// �������� ������� ������ �������
size_t vector_size(Vector *vector) {
	return vector->size;
}

// �������� ������ �������
void vector_resize(Vector *vector, size_t size) {
	int *temp = new int [size];
	if(size >= vector->size){
		for(size_t i = 0; i < vector->size; i++){
			temp[i] = vector->mass[i];
		}
	} else {
		for(size_t i = 0; i < size; i++){
			temp[i] = vector->mass[i];
		}
	}
	delete [] vector->mass;
	vector->mass = temp;
	vector->size = size;
}
