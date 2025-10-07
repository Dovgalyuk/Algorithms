#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef uintptr_t Data;

	typedef void FFree(void*);

	typedef struct Array Array;

	Array* array_create(size_t size, FFree* f);

	void array_delete(Array* arr);

	Data array_get(const Array* arr, size_t index);

	void array_set(Array* arr, size_t index, Data value);

	size_t array_size(const Array* arr);

#ifdef __cplusplus
}
#endif

#endif
