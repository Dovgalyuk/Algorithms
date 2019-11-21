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
	uint32_t hash(const KeyType& init);
	uint32_t hash(const char* init);
	uint32_t hash(const unsigned int x);
public:
	Hash_t(const KeyType& init);
	uint32_t get();
};

template <typename KeyType>
uint32_t Hash_t<KeyType>::hash(const KeyType& init)
{
	hash_data = 0;
	return 0;
}

template<>
uint32_t Hash_t<char*>::hash(const char* init)
{
	uint32_t hash_t = 0;
	for (size_t i = 0; init[i] != 0; i++)
	{
		hash_t += init[i];
		hash_t += (hash_t << 10);
		hash_t ^= (hash_t >> 6);
	}
	hash_t += (hash_t << 3);
	hash_t ^= (hash_t >> 11);
	hash_t += (hash_t << 15);
	return hash_t;
}

template<>
uint32_t Hash_t<unsigned int>::hash(unsigned int x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x;
}

template<>
uint32_t Hash_t<std::string>::hash(const std::string& init)
{
	return hash(init.c_str());
}

template <typename KeyType>
Hash_t<KeyType>::Hash_t(const KeyType& init)
{
	hash_data = hash(init);
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
	Vector<MapPair<KeyType, DataType>*>* data;
	void resize_cont(const size_t size);
public:
	Map();
	~Map();
	void add(const KeyType& first, const DataType& second);
	MapPair<KeyType, DataType>* find(const KeyType& first);
	bool RemovePair(const KeyType& first);
};

template <typename KeyType, typename DataType, unsigned int q>
void Map<KeyType, DataType, q>::resize_cont(const size_t size)
{
	Vector<MapPair<KeyType, DataType>*>* temp = new Vector<MapPair<KeyType, DataType>*>(size, NULL);
	for (size_t i = 0; i < data->size(); i++)
	{
		if ((*data)[i] == NULL)
			continue;
		uint32_t j = (*data)[i]->Hash() > temp->size() ? (*data)[i]->Hash() % temp->size() : (*data)[i]->Hash();
		while (temp[j] != NULL)
		{
			j = (j + q) % data->size();
		}
		(*temp)[j] = (*data)[i];
	}
	delete data;
	data = temp;
}

template <typename KeyType, typename DataType, unsigned int q>
Map<KeyType, DataType, q>::Map()
{
	data = new Vector<MapPair<KeyType, DataType>*>(100, NULL);
}

template <typename KeyType, typename DataType, unsigned int q>
Map<KeyType, DataType, q>::~Map()
{
	for (size_t i = 0; i < data->size(); i++)
		delete (*data)[i];
	delete data;
}

template <typename KeyType, typename DataType, unsigned int q>
void Map<KeyType, DataType, q>::add(const KeyType& first, const DataType& second)
{
	MapPair<KeyType, DataType>* temp = new MapPair<KeyType, DataType>(first, second);
	uint32_t i = temp->Hash() > data->size() ? temp->Hash() % data->size() : temp->Hash();
	uint32_t start = i;
	while ((*data)[i] != NULL)
	{
		i = (i + q) % data->size();
		if (i == start)
		{
			resize_cont(data->size() * 2);
			i = temp->Hash() > data->size() ? temp->Hash() % data->size() : temp->Hash();
			start = i;
		}
	}
	(*data)[i] = temp;
}

template <typename KeyType, typename DataType, unsigned int q>
MapPair<KeyType, DataType>* Map<KeyType, DataType, q>::find(const KeyType& first)
{
	Hash_t<KeyType> temp(first);
	uint32_t i = temp.get() > data->size() ? temp.get() % data->size() : temp.get();
	uint32_t start = i;
	while ((*data)[i] != NULL)
	{
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
	MapPair<KeyType, DataType>* temp = find(first);
	if (!temp)
		return false;
	uint32_t i = temp->Hash() > data->size() ? temp->Hash() % data->size() : temp->Hash();
	uint32_t start = i;
	while ((*data)[i] != temp)
	{
		i = (i + q) % data->size();
	}
	uint32_t save_hash = temp->Hash();
	uint32_t pos = i;
	(*data)[i] = NULL;
	i = (i + q) % data->size();
	delete temp;
	while ((*data)[i] != NULL && i != start)
	{
		if ((*data)[i]->Hash() == save_hash)
		{
			(*data)[pos] = (*data)[i];
			(*data)[i] = NULL;
			pos = i;
		}
		i = (i + q) % data->size();
	}
	return true;
}
#endif