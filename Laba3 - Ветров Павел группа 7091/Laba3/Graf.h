#ifndef Graf_H

#define Graf_H

#include "list.h"

typedef int Data;

struct Graf;
struct Iterator;

//--------GRAF-------//
Graf *graf_create(Data size);
void graf_delete(Graf *Graf);
void graf_set_vertex(Graf *Graf, Data value);
void graf_set_advertex(Graf *Graf, Data index_1, Data index_2);
void graf_delete_vertex(Graf *Graf, Data value);
void graf_delete_advertex(Graf *Graf, Data index_1, Data index_2);
bool graf_vertex_exist(Graf *Graf, Data index);
bool graf_edge_exist(Graf *Graf, Data index_1, Data index_2);
void graf_add_mark_edge(Graf *Graf, Data index_1, Data index_2, Data mark);
int graf_get_mark_edge(Graf *Graf, Data index_1, Data index_2);
void graf_add_mark_vertex(Graf *Graf, Data index, Data mark);
int graf_get_mark_vertex(Graf *Graf, Data index);
Data graf_size(Graf *Graf);
void graf_resize(Graf *Graf, Data size);

//------ITERATOR------//
Iterator *iterator_begin(Graf *Graf, Data index);
Iterator *iterator_end(Graf *Graf, Data index);
ListItem &iterator_current(Iterator *iterator);
int &iterator_value(Iterator *iterator);
void iterator_next(Iterator *iterator);
bool iterator_equal(Iterator *it1, Iterator *it2);



#endif
