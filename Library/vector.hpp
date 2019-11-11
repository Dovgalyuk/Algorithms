#ifndef VECTOR_H
#define VECTOR_H
template<typename Data>
class Vector
{
	Data* cont;
	size_t curr, real;
public:
	Vector();
	Vector(const Vector<Data>& source);
	Vector(const size_t size, Data& init);
	Vector(const size_t size);
	~Vector();
	Data get(const size_t index);
	void set(const size_t index, Data value);
	size_t size();
	void resize(const size_t size, Data& init);
	void resize(const size_t size);
	void push_back(const Data value);
	Data& operator[](const size_t index);
	Vector<Data>& operator= (Vector<Data>& source);
	bool operator== (Vector<Data>& source);
	bool operator!= (Vector<Data>& source);
	bool empty();
	void clear();
};

template<typename Data>
Vector<Data>::Vector()
{
	curr = 0;
	real = 2;
	cont = new Data[real];
};

template<typename Data>
Vector<Data>::Vector(const Vector<Data>& source)
{
	curr = source.curr;
	real = source.real;
	cont = new Data[real];
	for (size_t i = 0; i < curr; i++)
		cont[i] = source.cont[i];
};

template<typename Data>
Vector<Data>::Vector(const size_t size, Data& init)
{
	curr = size;
	real = size;
	cont = new Data[real];
	for (size_t i = 0; i < curr; i++)
		cont[i] = init;
};

template<typename Data>
Vector<Data>::Vector(const size_t size)
{
	curr = size;
	real = size;
	cont = new Data[real];
	for (size_t i = 0; i < curr; i++)
		cont[i] = Data();
};

template<typename Data>
Vector<Data>::~Vector()
{
	delete[] cont;
};

template<typename Data>
Data Vector<Data>::get(const size_t index)
{
	return cont[index];
};

template<typename Data>
void Vector<Data>::set(const size_t index, Data value)
{
	if (index + 1 > curr)
		resize(index + 1);
	cont[index] = value;
};

template<typename Data>
size_t Vector<Data>::size()
{
	return curr;
};

template<typename Data>
void Vector<Data>::resize(const size_t size, Data& init)
{
	if (size > real)
	{
		size_t new_size = real;
		while (new_size < size)
		{
			new_size *= 2;
		}
		Data* temp = new Data[new_size];
		for (size_t i = 0; i < curr; i++)
			temp[i] = cont[i];
		delete[] cont;
		cont = temp;
		real = new_size;
	}
	for (size_t i = curr; i < size; i++)
		cont[i] = init;
	curr = size;
};

template<typename Data>
void Vector<Data>::resize(const size_t size)
{
	resize(size, Data());
};

template<typename Data>
void Vector<Data>::push_back(const Data value)
{
	resize(curr + 1);
	cont[curr] = value;
	curr++;
};

template<typename Data>
Data& Vector<Data>::operator[](const size_t index)
{
	return cont[index];
};

template<typename Data>
Vector<Data>& Vector<Data>::operator= (Vector<Data>& source)
{
	if (&source == this)
		return *this;
	delete[] cont;
	curr = source.curr;
	real = source.real;
	cont = new Data[real];
	for (size_t i = 0; i < curr; i++)
		cont[i] = source.cont[i];
	return *this;
};

template<typename Data>
bool Vector<Data>::operator== (Vector<Data>& source)
{
	if (&source == this)
		return true;
	if (curr != source.curr)
		return false;
	for (size_t i = 0; i < curr; i++)
		if (cont[i] != source.cont[i])
			return false;
	return true;
};

template<typename Data>
bool Vector<Data>::operator!= (Vector<Data>& source)
{
	return !(*this == source);
};


template<typename Data>
bool Vector<Data>::empty()
{
	return !curr;
};

template<typename Data>
void Vector<Data>::clear()
{
	delete[] cont;
	curr = 0;
	real = 2;
	cont = new Data[real];
};
#endif