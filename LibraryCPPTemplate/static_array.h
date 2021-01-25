#ifndef STATICARR_H
#define STATICARR_H

typedef unsigned long long mysize_t;

template <typename T>
class StaticArray
{
private:
	T* _elem;
	mysize_t _size;
public:
	StaticArray(mysize_t size);
	~StaticArray();

	mysize_t get_size() const;
	T& operator[](mysize_t index);
	T operator[](mysize_t index) const;
	void copy(StaticArray& arr)
	{
		for (int i = 0; i < arr.get_size(); i++)
		{
			_elem[i] = arr[i];
		}
	}
};


template<typename T>
inline StaticArray<T>::StaticArray(mysize_t size)
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
inline mysize_t StaticArray<T>::get_size() const
{
	return _size;
}

template<typename T>
inline T& StaticArray<T>::operator[](mysize_t index)
{
	return _elem[index];
}

template<typename T>
inline T StaticArray<T>::operator[](mysize_t index) const
{
	return _elem[index];
}
#endif