#include "vector.h"
#include <cstddef>

struct Vector
{
	Data* data;
	size_t size;
	size_t pamyat;
};

Vector* vector_create() {
	Vector* vector = new Vector;
	vector->data = nullptr;
	vector->size = 0;
	vector->pamyat = 0;
	return vector;
}

void vector_delete(Vector* vector) {
	if (vector == nullptr) {
		return;
	}
	delete[] vector->data;
	delete vector;
}

Data vector_get(const Vector* vector, size_t index) {
	if (vector == nullptr || index >= vector->size) {
		return (Data)0;
	}
	return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value) {
	if (vector == nullptr || index >= vector->size) {
		return;
	}
	vector->data[index] = value;
}

size_t vector_size(const Vector* vector) {
	if (vector == nullptr) {
		return 0;
	}
	return vector->size;
}

void vector_resize(Vector* vector, size_t new_size) {

	if (vector == nullptr) {
		return;
	}

	if (new_size > vector->pamyat) {
		size_t new_pamyat = vector->pamyat * 2;

		if (new_pamyat < new_size) {
			new_pamyat = new_size;
		}

		Data* new_data = new Data[new_pamyat];
		for (size_t i = 0; i < vector->size; i++) {
			new_data[i] = vector->data[i];
		}

		delete[] vector->data;
		vector->data = new_data;
		vector->pamyat = new_pamyat;
	}

	if (new_size > vector->size) {
		for (size_t i = vector->size; i < new_size; i++) {
			vector->data[i] = (Data)0;
		}
	}
	vector->size = new_size;

}
