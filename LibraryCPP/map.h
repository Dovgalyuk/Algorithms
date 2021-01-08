#ifndef MAP_H
#define MAP_H

#include "splaytree.h"

struct Map;

Map* map_create();

bool map_add(Map* map, const Key& key, const Data& value);

Data map_get_value(Map* map, const Key& key);

bool map_set_value(Map* map, const Key& key, const Data& new_value);

bool map_remove(Map* map,const Key& key);

void map_delete(Map* map);

int map_tree_height(Map* map);

void map_print(Map* map);//DEBUG

#endif