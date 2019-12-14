#ifndef SET_H
#define SET_H

template <class T>
class Set
{
public:
	Set();
	Set(size_t size);
	~Set();
	void set_add(T element);
	void set_remove(T element);
	bool set_search(T element);
	size_t set_size();

private:
	size_t capacity;
	size_t realSize;
	T* array;
};

template <class T>
Set<T>::Set();

template <class T>
Set<T>::Set(size_t size);

template <class T>
Set<T>::~Set();

template <class T>
void Set<T>::set_add(T element);

template <class T>
void Set<T>::set_remove(T element);

template <class T>
bool Set<T>::set_search(T element);

template <class T>
size_t Set<T>::set_size();

#endif
