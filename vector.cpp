#include <stdlib.h>
#include "vector.h"
using namespace std;

struct Vector
{
    int* value;
    size_t size;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->value = NULL;
    vector->size = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    delete vector->value;
    delete vector;
}

//agarra um determinado elemento do vector
int vector_get(Vector *vector, size_t index) // o index é passado pelo indicador front da função queue_get
{
    if(index >= vector->size)
        return 0;
    return vector->value[index];
}

//insere um determinado elemento do vector
void vector_set(Vector *vector, size_t index, int value)
{
    if(index < vector->size) // compara o índice passado pelo ponteiro front ao tamanho do vector
        vector->value[index] = value;
}

size_t vector_size(Vector *vector)
{
    return vector->size;
}

//altera o tamanho do vector (diminue ou aumenta)
void vector_resize(Vector *vector, size_t size)
{
    size_t i;
    int* value = new int[size]; // ponteiro numa nova estrutura
    for(i = 0; i < size && i < vector->size; i++)
        value[i] = vector->value[i];
    for(size_t j = i; j < size; j++)
        value[j] = 0;
    delete [] vector->value;
    vector->value = value;
    vector->size = size;
    return;
}

