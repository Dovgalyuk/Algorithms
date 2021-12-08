#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include "../LibraryCPPTemplate/array.h" //else it uses the wrong array.h

struct iterator;
struct directed_graph;

bool NeighborListEmpty(iterator* iter);

int NextNeighborIndex(iterator* iter);

directed_graph* create_directed_graph(int vertexes_amount);

void delete_directed_graph(directed_graph* graph);

void add_vertex(directed_graph* graph); //add an vertex by copying the old array to the new array (where is 1 element more)

void add_edge(directed_graph* graph, int vertex1, int vertex2);

void remove_vertex(struct directed_graph* graph, int vertex); //add an vertex by copying the old array to the new array (where is 1 element less)

void remove_edge(directed_graph* graph, int vertex1, int vertex2);

void set_vertex_label(directed_graph* graph, int vertex_index, int vertex_label);

void set_edge_label(directed_graph* graph, int vertex1, int vertex2, int edge_label);

int get_vertex_label(directed_graph* graph, int vertex_index);

int get_edge_label(directed_graph* graph, int vertex1, int vertex2);

bool edge_exists(directed_graph* graph, int vertex1, int vertex2);

iterator* new_iterator(directed_graph* graph, int vertex);
#endif