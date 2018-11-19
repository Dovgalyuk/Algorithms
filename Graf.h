#ifndef GRAF_H
#define GRAF_H
#include "array.h"
//Stores integer values inside
typedef int Data;
struct Graf;
struct Iter;

//Creates a new iterator.
Iter* iter_create(Graf* graf, Data Vertex);

//Finds neighbors of Vertex.
void find_vertex(Iter* iter, Graf* graf, Data Vertex);

//Finds next iterator.
void next_iterator(Iter* iter, Graf* graf);

//Returns vertex.
Data get_vertex(const Iter* iter);

//Deletes the iterator.
void delete_iterator(Iter* iter);

//Creates a new graf.
Graf* graf_create(size_t CountOfVertex);

//Adds vertex in the graf.
void add_vertex(Graf* graf);

//Adds rib "StartVertex - EndVertex" in the graf.
void add_rib(Graf* graf, Data StartVertex, Data EndVertex);

//Deletes specified vertex in the graf.
void delete_vertex(Graf* graf, Data vertex);

//Deletes specified rib "StartVertex - EndVertex" in the graf.
void delete_rib(Graf* graf, Data StartVertex, Data EndVertex);

//Checks rib "StartVertex - EndVertex" in the graf.
//Function returns true, if graf has rib, else - false.
bool rib_is(const Graf* graf, Data StartVertex, Data EndVertex);

//Sets ves of the rib.
void ves_set(Graf* graf, Data StartVertex, Data EndVertex, int Ves);

//Returns ves of the rib.
int ves_get(const Graf* graf, Data StartVertex, Data EndVertex);
int get_ves(const Iter* it);

//Deletes the graf.
void delete_graf(Graf* graf);

//Returns true if there are no neighbors, else - false
bool is_neighbors(Iter* it);
#endif
