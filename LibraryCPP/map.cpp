#include "map.h"

struct Map
{
	HT_item* table;
	unsigned int N;
	unsigned int M;
};

Map* map_create()
{
	Map* map = new Map;
	map->table = create_table(Tsize);
	map->N = 0;
	map->M = Tsize;
	return map;
}

void map_delete(Map* map)
{
	table_delete(map->table);
	delete map;
}

bool ring_search_value(Map* map, const string key, string& value) //найти значение по ключу
{
	unsigned int count = 0;
	unsigned int hash = create_hash(key, map->M, count);
	while (count < map->M)
	{	
		if ((get_key(map->table, hash) == key) && (get_state(map->table, hash) == states::occupied))
		{
			value = get_value(map->table, hash);
			return true;
		}
		else if (get_state(map->table, hash) == states::empty)
			return false;
		else
		{
			count++;
			hash = create_hash(key, map->M, count);
		}
	}
	return false;
}

bool ring_search_clear(Map* map, const string key) //удалить значение по ключу (очистить ячейку)
{
	unsigned int count = 0;
	unsigned int hash = create_hash(key, map->M, count);
	while (count < map->M)
	{
		if ((get_key(map->table, hash) == key) && (get_state(map->table, hash) == states::occupied))
		{
			set_state(map->table, hash, states::empty_for_search);
			set_value(map->table, hash, "");
			map->N -= 1;
			return true;
		}
		else
		{
			count++;
			hash = create_hash(key, map->M, count);
		}
	}
	return false;
}

bool ring_search_empty(HT_item* table, const unsigned int M, const string key, unsigned int& hash_index)
{
	unsigned int count = 0;
	unsigned int hash = create_hash(key, M, count);
	while (count < M)
	{
		if (get_state(table, hash) != states::occupied)
		{
			hash_index = hash;
			return true;
		}
		else
		{
			count++;
			hash = create_hash(key, M, count);
		}
	}
	return false;
}

void table_resize(Map* map)
{
	unsigned int new_M = map->M * 2;
	HT_item* new_table = create_table(new_M);
	for (unsigned int i = 0; i < map->M; i++)
	{
		if (get_state(map->table, i) == states::occupied)
		{
			unsigned int hash_index = 0;			
			ring_search_empty(new_table, new_M, get_key(map->table, i), hash_index);
			set_key(new_table, hash_index, get_key(map->table, i));
			set_value(new_table, hash_index, get_value(map->table, i));
			set_state(new_table, hash_index, states::occupied);
		}
	}
	table_delete(map->table);
	map->M = new_M;
	map->table = new_table;
	new_table = nullptr;
}

void set_pair(Map* map, const string key, const string value) //добавить пару ключ-значение
{
	map->N += 1;
	if (((double)map->N / map->M) >= max_load_factor)
		table_resize(map);
	unsigned int hash_index = 0;
	ring_search_empty(map->table, map->M, key, hash_index);
	set_key(map->table, hash_index, key);
	set_value(map->table, hash_index, value);
	set_state(map->table, hash_index, states::occupied);
}