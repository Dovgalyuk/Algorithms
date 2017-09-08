#ifndef VECTOR_H
#define VECTOR_H

// ¬ списке хран€тс€ данные типа int,
// поэтому функции принимают и возвращают 
// данные этого типа

struct Vector;

// создание вектора
Vector *vector_create();

// удаление вектора
void vector_delete(Vector *vector);

// получить заданный элемент вектора
int vector_get(Vector *vector, size_t index);

// установить заданный элемент вектора
void vector_set(Vector *vector, size_t index, int value);

// получить текущий размер вектора
size_t vector_size(Vector *vector);

// изменить размер вектора
void vector_resize(Vector *vector, size_t size);

#endif
