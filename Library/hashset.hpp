#include "pair.hpp"

template <typename T>
class hashSet
{
	typedef Pair<T>* pair;
public:
	hashSet();
	~hashSet();
	void hash_add(T key);
	bool hash_remove(T key);
	bool hash_search(T key);
private:	
	const size_t q = 179;
	size_t realSize;
	size_t capacity;
	pair* ht;
	void hash_resize(size_t size);
};

template<typename T>
inline hashSet<T>::hashSet()
{
	realSize = 0;
	capacity = 100;
	ht = new pair[capacity];
	for (size_t i = 0; i < 100; i++)
	{
		ht[i] = NULL;
	}
}

template<typename T>
inline hashSet<T>::~hashSet()
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (ht[i] == (pair)0x000001)
		{
			continue;
		}
		delete ht[i];
	}
	delete[] ht;
}

template<typename T>
inline void hashSet<T>::hash_add(T key)
{
	if (capacity / 2 == realSize)
	{
		hash_resize(capacity * 2);
	}
	pair temp = new Pair<T>(key);
	size_t i = temp->get_hash() % capacity;
	size_t start = i;
	while (ht[i] != NULL && ht[i] != (pair)0x000001)
	{
		i = (i + q) % capacity;
		if (i == start)
		{
			hash_resize(capacity * 2);
			i = temp->get_hash() % capacity;
			start = i;
		}
	}
	ht[i] = temp;
	realSize++;
}

template<typename T>
inline bool hashSet<T>::hash_remove(T key)
{
	size_t i = Pair<T>(key).get_hash() % capacity;
	size_t start = i;
	while (ht[i] != NULL)
	{
		if (ht[i] == (pair)0x000001)
		{
			i = (i + q) % capacity;
			continue;
		}
		if (ht[i]->get_hash() == Pair<T>(key).get_hash() && ht[i]->get_key() == key)
		{
			break;
		}
		i = (i + q) % capacity;
		if (i == start)
		{
			return false;
		}
	}
	if (ht[i] == NULL)
	{
		return false;
	}
	delete ht[i];
	ht[i] = (pair)0x000001;
	realSize--;
	return true;
}

template<typename T>
inline bool hashSet<T>::hash_search(T key)
{
	size_t i = Pair<T>(key).get_hash() % capacity;
	size_t start = i;
	while (ht[i] != NULL)
	{
		if (ht[i] == (pair)0x000001)
		{
			i = (i + q) % capacity;
			continue;
		}
		if (ht[i]->get_hash() == Pair<T>(key).get_hash() && ht[i]->get_key() == key)
		{
			return true;
		}
		i = (i + q) % capacity;
		if (i == start)
		{
			break;
		}
	}
	return false;
}

template<typename T>
inline void hashSet<T>::hash_resize(size_t size)
{
	pair* temp = new pair[size];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = NULL;
	}
	for (size_t i = 0; i < capacity; i++)
	{
		if (ht[i] == NULL || ht[i] == (pair)0x000001)
		{
			continue;
		}
		size_t j = ht[i]->get_hash() % size;
		while (temp[j] != NULL)
		{
			j = (j + q) % size;
		}
		temp[j] = ht[i];
	}
	delete[] ht;
	ht = temp;
	capacity = size;
}