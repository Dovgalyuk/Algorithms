#include <stdlib.h>
#include "vector.h"

struct Vector
{
	size_t size = 0;
	int *number;
};

Vector *vector_create()
{
	Vector *vector = new Vector;
    return vector;
}

void vector_delete(Vector *vector)
{
	delete vector;
}

int vector_get(Vector *vector, size_t index)
{
    if(vector->size<index)
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
	if(index>vector->size)
	{
		int *mas = new int[index];
		for(size_t i=0;i<vector->size;i++)
		{
			mas[i] = vector->number[i];
		}
		for(size_t i=vector->size;i<index;i++)
		{
			mas[i]=0;
		}
		mas[index]=value;
		delete [] vector->number;
		vector->number = mas;
		vector->size=index;
	}
	else
	{
		vector->number[index]=value;

	}

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
		delete [] vector->number;
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
		delete [] vector->number;
		vector->number = mas;
		vector->size=size;
	}
	else
	{
		return;
	}


}
