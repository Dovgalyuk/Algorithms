#include "array.h"

struct Array
{
	int size;
	int* m;
};

Array* array_create(size_t size)
{
	Array *tmp = new Array;
	tmp->size = size;
	tmp->m = new int[ArrSize];
	memset(tmp->m, 0, sizeof(int)*ArrSize);
	return tmp;
}

// delete array, free memory
void array_delete(Array *arr)
{
	delete[] arr->m;
	delete arr;
}

size_t array_size(Array *arr)
{
    return arr->size;
}

// Set array size
void set_array_size(Array *arr, int size)
{
	arr->size = size;
}

//get pointer
int* get_pointer(Array *arr, int index)
{
	return &arr->m[index];
}