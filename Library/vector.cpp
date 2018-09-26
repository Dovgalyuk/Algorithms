#include <stdlib.h>
#include "vector.h"

struct Vector
{
	size_t size = 0;
	int *number = new int[0];
};

Vector *vector_create()
{
	Vector *vector = new Vector;
    return vector;
}

void vector_delete(Vector *vector)
{
	delete[](vector->number);
	delete vector;
}

int vector_get(Vector *vector, size_t index)
{
    if(vector->size<=index)
    {
    	std::cout<<"Invalid size"<<std::endl;
    	return 0;
    }
    else
	{
    	return vector->number[index];
	}

}

void vector_set(Vector *vector, size_t index, int value)
{
	if(index>=vector->size)
	{
		vector_resize(vector, index + 1);
	}
	vector->number[index] = value;
}

size_t vector_size(Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if(vector->size>size)
	{
		int *mas = new int[size];
		for(size_t i=0;i<size;i++)
		{
			mas[i]=vector->number[i];
		}
		delete [] (vector->number);
		vector->number = mas;
		vector->size=size;

	}
	if (vector->size<size)
	{
		int *mas = new int[size];
		for(size_t i=0;i<vector->size;i++)
		{
			mas[i] = vector->number[i];
		}
		for(size_t i=vector->size;i<size;i++)
		{
			mas[i]=0;
		}
		delete [] (vector->number);
		vector->number = mas;
		vector->size=size;
	}
	else
	{
		return;
	}
}
