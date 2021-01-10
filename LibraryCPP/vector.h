#ifndef VECTOR_H
#define VECTOR_H

typedef int Data;

struct Vector
{
private:
	size_t Size;
	Data* Elem;
public:
	Vector()
		:Size(0)
	{
		Elem = new Data[0];
		Resize(1);
	}
	Vector(size_t size)
		:Size(0)
	{
		Elem = new Data[Size];
		Resize(size);
	}
	~Vector()
	{
		delete[] Elem;
	}
	Data GetValue(size_t index) const
	{
		return Elem[index];
	}
	void Set(size_t index, Data value)
	{
		if (index >= Size) Resize(index * 2);
		Elem[index] = value;
	}
	size_t GetSize() const
	{
		return Size;
	}
	void Resize(size_t size)
	{
		size_t new_size = 0;
		Data* elem;
		if (size <= Size)
		{
			new_size = size;
			elem = new Data[new_size];

			for (int i = 0; i < size; i++)
			{
				elem[i] = Elem[i];
			}
		}
		else
		{
			new_size = size > Size * 2 ? size : Size * 2;
			elem = new Data[new_size];

			for (int i = 0; i < Size; i++)
			{
				elem[i] = Elem[i];
			}
			int i = Size;
			if (i < 0) i = 0;
			for (i; i < new_size; i++)
			{
				elem[i] = 0;
			}
		}

		delete[] Elem;
		Elem = elem;
		Size = new_size;
	}
};

#endif