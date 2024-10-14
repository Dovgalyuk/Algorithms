#include "array.h"

struct Array {
	Data elem;
	size_t size;
};

Array* array_create(size_t size) {
	Array* array = new Array[size];
	array->size = size;
	return array;
}

size_t array_size(const Array* arr) {
	return arr->size;
}

void array_set(Array* arr, size_t index, Data x) {
	arr[index].elem = x;
}

Data array_get(const Array* arr, size_t index) {
	return arr[index].elem;
}

void array_delete(Array* arr) {
	delete[] arr;
	arr = nullptr;
}