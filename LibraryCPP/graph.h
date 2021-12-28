#ifndef GRAPH_H
#define GRAPH_H

struct iterator;
struct graph;

graph* create_graph(int vertex_amount);

iterator* new_iterator(graph* dir_graph,int vertex);

void graph_del_iterator(iterator* iter);

void graph_del_graph(graph* graph);

void graph_add_vertex(struct graph * dir_graph);

void graph_add_edge(graph*dir_graph,int vertex_1,int vertex_2,int input_weight);

void graph_remove_vertex(struct graph* dir_graph,int vertex);

void graph_remove_edge(graph*dir_graph,int vertex_1,int vertex_2);

void graph_set_vertex_label(graph* dir_graph,int vertex_index,int vertex_label);

void graph_set_edge_label(graph* dir_graph,int vertex_1,int vertex_2,int edge_label);

int graph_get_vertex_label(graph* dir_graph,int vertex_index);

int graph_get_edge_label(graph* dir_graph,int vertex_1,int vertex_2);

bool graph_Exists_edge(graph* dir_graph,int vertex_1,int vertex_2);

bool graph_Neighboor_empty(iterator* iter);

bool graph_Neighboor_next(iterator* iter);

#endif