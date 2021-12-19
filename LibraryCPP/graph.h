#ifndef GRAPH_H
#define GRAPH_H

struct iterator;
struct graph;

void del_iterator(iterator* iter);

void del_graph(graph* graph);

void add_vertex();

void add_edge();

void remove_vertex();

void remove_edge();

void set_vertex();

void set_edge();

int get_vertex();

bool Exists_edge();

int get_edge();

bool Neighboor_empty();

bool Neighboor_next();


#endif