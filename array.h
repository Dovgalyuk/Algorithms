typedef int Data;
struct Array
{
	Data* _arr;
	int _n;

	Array(int n)
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
Array array_create(int size)
{
	return Array(size);
}

// delete array, free memory
// returns specified array element
Data array_get(const Array arr, int index)
{// return (Data)0;
	if (index >= array_size(arr))
		return 0;
	else
		return arr._arr[index];
}

// sets the specified array element to the value
void array_set(Array arr, int index, Data value)
{
	if (index >= array_size(arr))
		return;
	else
		arr._arr[index] = value;
}
