#include "hashtable.h"

void alg_hash(unsigned int& hash, const string key, const unsigned int M)
{
	for (unsigned int i = 0; i < key.length(); i++)
		hash = hash * prime + key[i];
}

unsigned int create_hash(const string key, const unsigned int M, int i)
{
	unsigned int hash = 0;
	alg_hash(hash, key, M);
	return (hash + i) % M;
}

struct HT_item
{
	string key;
	string value;
	states item_state;
};

HT_item* create_table(const unsigned int M)
{
	HT_item* table = new HT_item[M];
	for (unsigned int i = 0; i < M; i++)
	{
		table[i].key = table[i].value = "";
		table[i].item_state = states::empty;
	}
	return table;
}

void table_delete(HT_item* table)
{
	delete[] table;
	table = nullptr;
}

string get_key(HT_item* table, const unsigned int i)
{
	return table[i].key;
}

string get_value(HT_item* table, const unsigned int i)
{
	return table[i].value;
}

states get_state(HT_item* table, const unsigned int i)
{
	return table[i].item_state;
}

void set_key(HT_item* table, const unsigned int i, const string key)
{
	table[i].key = key;
}

void set_value(HT_item* table, const unsigned int i, const string value)
{
	table[i].value = value;
}

void set_state(HT_item* table, const unsigned int i, states state)
{
	table[i].item_state = state;
}