#ifndef STATICARR_H
#define STATICARR_H

template <typename T>
class StaticArray
{
private:
	T* _elem;
	size_t _size;
public:
	StaticArray(size_t size);
	~StaticArray();

	size_t get_size() const;
	T& operator[](size_t index);
	T operator[](size_t index) const;
	void copy(StaticArray& arr)
	{
		for (int i = 0; i < arr.get_size(); i++)
		{
			_elem[i] = arr[i];
		}
	}
};

template<typename T>
inline StaticArray<T>::StaticArray(size_t size)
{
	_size = size;
	_elem = new T[size];
}

template<typename T>
inline StaticArray<T>::~StaticArray()
{
	delete[] _elem;
}

template<typename T>
inline size_t StaticArray<T>::get_size() const
{
	return _size;
}

template<typename T>
inline T& StaticArray<T>::operator[](size_t index)
{
	return _elem[index];
}

template<typename T>
inline T StaticArray<T>::operator[](size_t index) const
{
	return _elem[index];
}

#endif