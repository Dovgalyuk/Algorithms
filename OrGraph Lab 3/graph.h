#ifndef GRAPH_H
#define GRAPH_H
#include "vector.h"

typedef int Data;
struct Graph;
struct Iterator;

Iterator* iterator_create(Graph* graph, int vertex);

void find_pair(Iterator* iterator, int vertex);

void next_iterator(Iterator* iterator);

Data get_vertex(Iterator* iter);

void delete_iterator(Iterator* iterator);

Graph* graph_create(size_t CountOfVertex);

void add_vertex(Graph* graph);

void add_edge(Graph* graph, int start_vertex, int end_vertex);

void delete_vertex(Graph* graph, int vertex);

void delete_edge(Graph* graph, int start_vertex, int end_vertex);

bool is_edge(Graph* graph, int start_vertex, int end_vertex);

void set_weight(Graph* graph, int start_vertex, int end_vertex, int weight);

int get_weight(Graph* graph, int start_vertex, int end_vertex);

int iterator_weight(Iterator* iterator);

void delete_graph(Graph* graph);

bool is_neighbors(Iterator* iterator);
#endif
