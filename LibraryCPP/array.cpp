#include "array.h"

struct Array
{
    size_t count ;
    Data *arr;
     Array(size_t n) {
     count = n;
     arr = new Data[count];

     }
     ~Array(){
        delete[] arr;
     }

};

// create array
Array *array_create(size_t size)
{
return new Array(size);
   
}

// delete array, free memory
void array_delete(Array *arr)
{
  delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    
    if (index >= array_size(arr))
    {
        return 0;
    }
    else 
    {
        return arr->arr[index];
    }

}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= array_size(arr))
    {
        return ;
    }
    else 
    {
        arr->arr[index]=value;
    }
}

// returns array size
size_t array_size(const Array *arr)
{
   return arr->count;
}
