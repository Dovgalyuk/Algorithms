#ifndef SET_H
#define SET_H
#include "splay_tree.h"

struct Set;

Set* set_create(const Key key);

void set_insert(Set* set, const Key key);

bool set_find(Set* set, const Key key);

void set_erase(Set* set, const Key key);

Set* set_delete(Set* set);

#endif