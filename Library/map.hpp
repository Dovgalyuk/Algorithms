#ifndef MAP_H
#define MAP_H
#include <string>
#include "vector.hpp"

#ifndef __uint32_t_defined
typedef unsigned int		uint32_t;
# define __uint32_t_defined
#endif

template <typename KeyType>
class Hash_t
{
	uint32_t hash_data;
public:
	Hash_t(const KeyType& init);
	uint32_t get();
	Hash_t(const char*& init);
};

template <typename KeyType>
Hash_t<KeyType>::Hash_t(const KeyType& init)
{
	hash_data = &init;
}

template <>
Hash_t<std::string>::Hash_t(const std::string& init)
{
	hash_data = 0;
	for (size_t i = 0; i < init.size(); i++)
	{
		hash_data += init[i];
		hash_data += (hash_data << 10);
		hash_data ^= (hash_data >> 6);
	}
	hash_data += (hash_data << 3);
	hash_data ^= (hash_data >> 11);
	hash_data += (hash_data << 15);
}

template <>
Hash_t<unsigned int>::Hash_t(const unsigned int& init)
{
	hash_data = init;
	hash_data = ((hash_data >> 16) ^ hash_data) * 0x45d9f3b;
	hash_data = ((hash_data >> 16) ^ hash_data) * 0x45d9f3b;
	hash_data = (hash_data >> 16) ^ hash_data;
}

template <>
Hash_t<int>::Hash_t(const int& init)
{
	hash_data = init;
	hash_data = ((hash_data >> 16) ^ hash_data) * 0x45d9f3b;
	hash_data = ((hash_data >> 16) ^ hash_data) * 0x45d9f3b;
	hash_data = (hash_data >> 16) ^ hash_data;
}

template <>
Hash_t<char*>::Hash_t(const char*& init)
{
	hash_data = 0;
	for (size_t i = 0; init[i] != 0; i++)
	{
		hash_data += init[i];
		hash_data += (hash_data << 10);
		hash_data ^= (hash_data >> 6);
	}
	hash_data += (hash_data << 3);
	hash_data ^= (hash_data >> 11);
	hash_data += (hash_data << 15);
}

template <typename KeyType>
uint32_t Hash_t<KeyType>::get()
{
	return hash_data;
}

template <typename KeyType, typename DataType>
class MapPair
{
	Hash_t<KeyType> hash;
	KeyType Key;
	DataType Data;
public:
	MapPair(const KeyType& first, const DataType& second);
	uint32_t Hash();
	const KeyType& first();
	DataType& second();
};

template <typename KeyType, typename DataType>
MapPair<KeyType, DataType>::MapPair(const KeyType& first, const DataType& second) : Key(first), Data(second), hash(first)
{}

template <typename KeyType, typename DataType>
uint32_t MapPair<KeyType, DataType>::Hash()
{
	return hash.get();
}

template <typename KeyType, typename DataType>
const KeyType& MapPair<KeyType, DataType>::first()
{
	return Key;
}

template <typename KeyType, typename DataType>
DataType& MapPair<KeyType, DataType>::second()
{
	return Data;
}

template <typename KeyType, typename DataType, unsigned int q = 1>
class Map
{
public:
	typedef MapPair<KeyType, DataType>* Pair;
private:
	Vector<Pair>* data;
	void resize_cont(const size_t size);
	size_t used;
public:
	Map();
	~Map();
	void add(const KeyType& first, const DataType& second);
	Pair find(const KeyType& first);
	bool RemovePair(const KeyType& first);
};

template <typename KeyType, typename DataType, unsigned int q>
void Map<KeyType, DataType, q>::resize_cont(const size_t size)
{
	Vector<Pair>* temp = new Vector<Pair>(size, NULL);
	for (size_t i = 0; i < data->size(); i++)
	{
		if ((*data)[i] == NULL || (*data)[i] == (Pair)0x000001)
			continue;
		uint32_t j = (*data)[i]->Hash() % temp->size();
		while ((*temp)[j] != NULL)
		{
			j = (j + q) % temp->size();
		}
		(*temp)[j] = (*data)[i];
	}
	delete data;
	data = temp;
}

template <typename KeyType, typename DataType, unsigned int q>
Map<KeyType, DataType, q>::Map()
{
	data = new Vector<Pair>(100, NULL);
	used = 0;
}

template <typename KeyType, typename DataType, unsigned int q>
Map<KeyType, DataType, q>::~Map()
{
	for (size_t i = 0; i < data->size(); i++)
	{
		if ((*data)[i] == (Pair)0x000001)
		{
			continue;
		}
		delete (*data)[i];
	}
	delete data;
}

template <typename KeyType, typename DataType, unsigned int q>
void Map<KeyType, DataType, q>::add(const KeyType& first, const DataType& second)
{
	Pair temp = new MapPair<KeyType, DataType>(first, second);
	uint32_t i = temp->Hash() % data->size();
	uint32_t start = i;
	if (data->size() / 2 == used)
		resize_cont(data->size() * 2);
	while ((*data)[i] != NULL && (*data)[i] != (Pair)0x000001)
	{
		i = (i + q) % data->size();
		if (i == start)
		{
			resize_cont(data->size() * 2);
			i = temp->Hash() % data->size();
			start = i;
		}
	}
	(*data)[i] = temp;
	used++;
}

template <typename KeyType, typename DataType, unsigned int q>
typename Map<KeyType, DataType, q>::Pair Map<KeyType, DataType, q>::find(const KeyType& first)
{
	Hash_t<KeyType> temp(first);
	uint32_t i = temp.get() % data->size();
	uint32_t start = i;
	while ((*data)[i] != NULL)
	{
		if ((*data)[i] == (Pair)0x000001)
		{
			i = (i + q) % data->size();
			continue;
		}
		if ((*data)[i]->Hash() == temp.get() && (*data)[i]->first() == first)
			return (*data)[i];
		i = (i + q) % data->size();
		if (i == start)
			break;
	}
	return NULL;
}

template <typename KeyType, typename DataType, unsigned int q>
bool Map<KeyType, DataType, q>::RemovePair(const KeyType& first)
{
	Hash_t<KeyType> temp(first);
	uint32_t i = temp.get() % data->size();
	uint32_t start = i;
	while ((*data)[i] != NULL)
	{
		if ((*data)[i] == (Pair)0x000001)
		{
			i = (i + q) % data->size();
			continue;
		}
		if ((*data)[i]->Hash() == temp.get() && (*data)[i]->first() == first)
			break;
		i = (i + q) % data->size();
		if (i == start)
			return false;
	}
	if ((*data)[i] == NULL)
		return false;
	uint32_t j = (i + q) % data->size();
	delete (*data)[i];
	(*data)[i] = (Pair)0x000001;
	//resize_cont(data->size());
	while ((*data)[j] != NULL && j != start)
	{
		if ((*data)[j] == (Pair)0x000001)
		{
			j = (j + q) % data->size();
			continue;
		}
		if ((*data)[j]->Hash() == temp.get())
		{
			(*data)[i] = (*data)[j];
			(*data)[j] = (Pair)0x000001;
			i = j;
		}
		j = (j + q) % data->size();
	}
	used--;
	return true;
}
#endif