#include "array.h"


struct Array
{
    int n;
    Array* ptr;
};

// create array
Array* array_create(size_t size)
{
    if (size == 0) {
        return nullptr;
    }
    
    Array* head = new Array;
    Array* current = head;
    
    current->n = 0;
    current->ptr = nullptr;
    
    for (size_t i = 0; i < size; i++) {
        current->ptr = new Array;
        current = current->ptr;
        current->n = 0;
        current->ptr = nullptr;
    }
    
    return head;
}

// delete array, free memory
void array_delete(Array *arr)
{
    Array *current = arr;
    while(current != nullptr){
        Array *nextVoulm = current->ptr;
        delete arr;
        current = nextVoulm;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    int voulm;
    const Array *current = arr;
    for (size_t i = 0; i < index; i++){
        if (current->ptr == nullptr){
            return (Data)0;
        }
        current = current->ptr;
    }
    return (Data)(current->n);
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    Array *current = arr;
    for(int i = 0; i < index; i++){
        if(current->ptr == nullptr){
            return;
        }
        current = current->ptr;
    }
    current->n = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    size_t size;
    const Array *current;
    while (current->ptr != nullptr){
        size++;
        current = current->ptr;
    }
    return size;
}
