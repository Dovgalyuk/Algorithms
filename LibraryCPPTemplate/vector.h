#ifndef VECTOR_H
#define VECTOR_H

// Vector (dynamic array)
// Stores integer values inside
typedef int Data;

template <typename T>
struct Vector
{
private:
	size_t _size;
	T* _elem;
	size_t _space;
public:
	Vector()
		:_size(0), _space(0)
	{
		_elem = new T[_size];
	}
	Vector(size_t size)
		:_size(0), _space(0)
	{
		_elem = new T[_size];
		Resize(size);
	}
	~Vector()
	{
		delete[] _elem;
	}
	T GetValue(size_t index) const
	{
		return _elem[index];
	}
	void Set(size_t index, T value)
	{
		if (index > _size) Resize(index);
		_elem[index] = value;
	}
	size_t GetSize() const
	{
		return _size;
	}
	void Resize(size_t size)
	{
		//	if (size > _size)
		//	{
		//		Reserve(size);
		//		for (int i = _size; i < size; i++)
		//			_elem[i] = Data();
		//	}
		//	_size = size;
		if (size < _size)
		{
			_size = size;
		}
		else 
		{
			size_t newSize = size * 2;
			T* newVector = new T[newSize];
			for (int i = 0; i < _size; i++)
			{
				newVector[i] = _elem[i];
			}
			if (_elem != nullptr) delete[] _elem;
			_elem = newVector;
			_size = size;
			_space = newSize;
		}
	}
	size_t GetCapacity() const
	{
		return _space;
	}
};

//// Creates vector
//Vector *vector_create();
//
//// Deletes vector structure and internal data
//void vector_delete(Vector *vector);
//
//// Retrieves vector element with the specified index
//Data vector_get(const Vector *vector, size_t index);
//
//// Sets vector element with the specified index
//void vector_set(Vector *vector, size_t index, Data value);
//
//// Retrieves current vector size
//size_t vector_size(const Vector *vector);
//
//// Changes the vector size (may increase or decrease)
//// Should be O(1) on average
//void vector_resize(Vector *vector, size_t size);

#endif