#include "hashtable.h"

#ifndef MAP_H
#define MAP_H

const int Tsize = 21;
const double max_load_factor = 0.66;

struct Map;

Map* map_create();

void map_delete(Map* map);

void map_delete(Map* map);

bool ring_search_value(Map* map, const string key, string& value);

bool ring_search_empty(HT_item* table, const unsigned int M, const string key, unsigned int& hash_index);

bool ring_search_clear(Map* map, const string key);

void table_resize(Map* map);

void set_pair(Map* map, const string key, const string value);

#endif