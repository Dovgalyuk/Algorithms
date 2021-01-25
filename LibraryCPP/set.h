#ifndef SET_H
#define SET_H
#include "avltree.h"
#include <iostream>

struct Set;

Set* set_create();

void set_insert(Set* set, const Data& data);

Data& set_find(Set* set, const Data& key);

bool set_remove(Set* set, const Data& key);

void set_output(Set* set);

void set_delete(Set* set);

#endif