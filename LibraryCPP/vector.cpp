#include "vector.h"
#include "algorithm"
#include <cstdlib>
using namespace std;

struct Vector {
	Data* data;
	size_t size;
	size_t capacity;
};

Vector* vector_create() {
	Vector* vector = (Vector*)malloc(sizeof(Vector));
	if (vector != nullptr) {
		vector->data = (Data*)malloc(10 * sizeof(Data));
		vector->size = 0;
		vector->capacity = 10;
	}
	return vector;
}

void vector_delete(Vector* vector) {
	free(vector->data);
	free(vector);
}

Data vector_get(const Vector* vector, size_t index) {
	return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value) {
	vector->data[index] = value;
}

size_t vector_size(const Vector* vector) {
	return vector->size;
}

void vector_resize(Vector* vector, size_t size) {
	if (size > vector->capacity) {
		size_t new_capacity = max(size, vector->capacity * 2);
		Data* new_data = (Data*)realloc(vector->data, new_capacity * sizeof(Data));
		vector->data = new_data;
		vector->capacity = new_capacity;
	}
	vector->size = size;
}
