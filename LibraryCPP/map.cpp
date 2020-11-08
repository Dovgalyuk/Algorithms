#include "map.h"

struct Map
{
   Node* root;
};

Map* map_create()
{
   Map* mp = new Map;
   return mp;
}

void map_insert(Map* mp, const Data& data, const Key& key)
{
   mp->root = node_insert(mp->root, data, key);
}

Data map_getData(Map* mp, const Key& key)
{
   return node_getData(node_search(mp->root, key));
}

void map_remove(Map* mp, const Key& key)
{
   mp->root = node_remove(mp->root, key);
}

void map_delete(Map* mp)
{
   mp->root = node_delete(mp->root);
}
