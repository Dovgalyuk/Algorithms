#ifndef STACK_H
#define STACK_H
#include "static_array.h"

typedef int Data;

template <typename T>
struct Stack
{
private:
	StaticArray<T> _array = StaticArray<T>(10);
	size_t _index;
public:
	Stack();
	~Stack();
	void push(T data);
	T get();
	void pop();
	bool empty();
};


#endif

template<typename T>
inline Stack<T>::Stack()
{
	_index = -1;
}

template<typename T>
inline Stack<T>::~Stack()
{
	//delete _array;
}

template<typename T>
inline void Stack<T>::push(T data)
{
	_index++;
	if (_index >= _array.get_size())
	{
		StaticArray<T> new_array = StaticArray<T>(_array.get_size() * 2);
		new_array = _array;
		new_array.copy(_array);
	}
	_array[_index] = data;
}

template<typename T>
inline T Stack<T>::get()
{
	return _array[_index];
}

template<typename T>
inline void Stack<T>::pop()
{
	if (!empty())
		_index--;
}

template<typename T>
inline bool Stack<T>::empty()
{
	return _index == -1;
}
