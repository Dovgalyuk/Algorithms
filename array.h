#pragma once
typedef int Data;

struct Array
{
	Data* _arr;
	size_t _n;

	Array(size_t n)
	{
		_n = n;
		_arr = new Data[_n];
	}


};

// returns array size
size_t array_size(const Array arr)
{
	//return 0;
	return arr._n;
}

// create array
Array array_create(size_t size)
{
	return Array(size);
}

// delete array, free memory
// returns specified array element
Data array_get(const Array arr, size_t index)
{// return (Data)0;
	if (index >= array_size(arr))
		return 0;
	else
		return arr._arr[index];
}

// sets the specified array element to the value
void array_set(Array arr, size_t index, Data value)
{
	if (index >= array_size(arr))
		return;
	else
		arr._arr[index] = value;
}