#ifndef MAP_H
#define MAP_H

#include "avltree.h"

struct Map;

// Create new map
Map* map_create();

// Inserts a new data
void map_insert(Map* mp, const Data& data, const Key& key);

// Deletes a data by key
void map_remove(Map* mp, const Key& key);

// Returns data from map by key
Data map_getData(Map* mp, const Key& key);

// Delete map, free memory
void map_delete(Map* mp);

#endif
