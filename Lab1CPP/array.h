#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

struct Array;

Array* array_create(std::size_t size);
void array_delete(Array** array);

std::size_t array_size(const Array* array);

void array_set(Array* array, std::size_t index, int value);
int array_get(const Array* array, std::size_t index);

#endif