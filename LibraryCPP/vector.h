#ifndef VECTOR_H
#define VECTOR_H

typedef int Data;

struct Vector
{
private:
	size_t Capacity;
	size_t Size;
	Data* Elem;
public:
	Vector()
		:Capacity(0), Size(0)
	{
		Elem = new Data[0];
		Resize(1);
	}
	Vector(size_t capacity)
		:Capacity(0), Size(0)
	{
		Elem = new Data[Capacity];
		Resize(capacity);
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
		if (index >= Capacity) Resize(index * 2);
		Elem[index] = value;
		Size++;
	}
	size_t GetSize() const
	{
		return Size;
	}
	size_t GetCapacity() const
	{
		return Capacity;
	}
	void Resize(size_t size)
	{
		if (size > Capacity)
		{
			Recap(size * 2);
		}
		Size = size;
	}
	void Recap(size_t capacity)
	{
		size_t new_cap = 0;
		Data* elem;
		if (capacity <= Capacity)
		{
			new_cap = capacity;
			elem = new Data[new_cap];

			for (int i = 0; i < capacity; i++)
			{
				elem[i] = Elem[i];
			}
		}
		else
		{
			new_cap = capacity > Capacity * 2 ? capacity : Capacity * 2;
			elem = new Data[new_cap];

			for (int i = 0; i < Capacity; i++)
			{
				elem[i] = Elem[i];
			}
			int i = Capacity;
			if (i < 0) i = 0;
			for (i; i < new_cap; i++)
			{
				elem[i] = 0;
			}
		}

		delete[] Elem;
		Elem = elem;
		Capacity = new_cap;
	}

};

#endif