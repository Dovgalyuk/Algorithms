#include "array.h"
#ifndef Graf_H
#define Graf_H

struct Graf;
struct Iterator;

//assign iterator
void assign_it(Iterator* it1, Iterator* it2);
//dereference iterator
int& DerColori(Iterator* it);
int& DerColorj(Iterator* it);
int& DerCur(Iterator* it);
int& DerVis(Iterator* it);
//up iterator
void up(Iterator* it);
//compare iterator 
bool comp(Iterator* it1, Iterator* it2);

//begin and end iterator
Iterator* create_iterator_begin(Graf* graf, int vertex);
Iterator* create_iterator_end(Graf* graf, int vertex);

//create graf
Graf* graf_create(int size);

//add vertex
void add_vertex(Graf *graf);
//add edge
void add_edge(Graf *graf, int Fvertex, int Tvertex);
//delete vertex
void delete_vertex(Graf *graf, int index);
//delete egde
void delete_egde(Graf *graf, int Fvertex, int Tvertex);

//add mark edge
void add_mark_edge(Graf *graf, int Fvertex, int Tvertex, int mark);
//add mark vertex
void add_mark_vertex(Graf *graf, int vertex, int mark);
//get mark edge
int get_mark_edge(Graf *graf, int Fvertex, int Tvertex);
//get mark vertex
int get_mark_vertex(Graf *graf, int vertex);

//check for the existence of an edge
bool Is_edge(Graf *graf, int Fvertex, int Tvertex);

//delete graf
void delete_graf(Graf *graf);
//delete iterator
void delete_iterator(Iterator* it);
#endif