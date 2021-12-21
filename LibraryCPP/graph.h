#ifndef GRAPH_H
#define GRAPH_H

struct iterator;
struct graph;

void graph_del_iterator(iterator* iter);

void graph_del_graph(graph* graph);

void graph_add_vertex();

void graph_add_edge();

void graph_remove_vertex();

void graph_remove_edge();

void graph_set_vertex();

void graph_set_edge();

int graph_get_vertex();

bool graph_Exists_edge();

int graph_get_edge();

bool graph_Neighboor_empty();

bool graph_Neighboor_next();


#endif