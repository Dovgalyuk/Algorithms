#ifndef GRAPH_H
#define GRAPH_H

struct iterator;
struct graph;

graph* create_graph(int vertex_amount);

iterator* new_iterator(graph* dir_graph,int vertex);

void graph_del_iterator(iterator* iter);

void graph_del_graph(graph* graph);

void graph_add_vertex(struct graph * dir_graph);

void graph_add_edge(graph*dir_graph,int vertex_1,int vertex_2);

void graph_remove_vertex(struct graph* dir_graph,int vertex);

void graph_remove_edge(graph*dir_graph,int vertex_1,int vertex_2);

void graph_set_vertex(graph* dir_graph,int vertex_index,int vertex_label);

void graph_set_edge();

int graph_get_vertex();

bool graph_Exists_edge();

int graph_get_edge();

bool graph_Neighboor_empty();

bool graph_Neighboor_next();


#endif