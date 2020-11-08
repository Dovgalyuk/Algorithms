#ifndef MAP_H
#define MAP_H

#include "avltree.h"

struct Map;

Map* map_create();

void map_insert(Map* mp, const Data& data, const Key& key);

void map_remove(Map* mp, const Key& key);

Data map_getData(Map* mp, const Key& key);

void map_delete(Map* mp);

#endif
