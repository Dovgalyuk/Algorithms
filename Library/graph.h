#ifndef GRAPH_H
#define GRAPH_H

// Graph(Directed)
// Stores integer values inside
#include "defines.h"
#include "list.h"

struct Graph;
struct Vertex;
struct Edge;

// Creates new graph
Graph* graph_create(const size_t vertex_count);

// Destroys the graph and frees the memory
void graph_delete(Graph* graph);

// Adds new vertex to graph
size_t graph_add_vertex(Graph* graph);

// Adds new edge to graph
void graph_add_edge(Graph* graph, const size_t head, const size_t tail);

// Removes specified vertex from graph
void graph_remove_vertex(Graph* graph, const size_t vertex);

// Removes specified edge from graph
void graph_remove_edge(Graph* graph, const size_t head, const size_t tail);

// Returns true if there is edge directed from head to tail
bool graph_check_edge(const Graph* graph, const size_t head, const size_t tail);

// Sets specified vertex mark
void graph_set_vertex_mark(Graph* graph, const size_t vertex, const Mark mark);

// Returns specified vertex mark
Mark graph_get_vertex_mark(const Graph* graph, const size_t vertex);

// Sets specified edge mark
void graph_set_edge_mark(Graph* graph, const size_t head, const size_t tail, const Mark mark);

// Returns specified edge mark
Mark graph_get_edge_mark(const Graph* graph, const size_t head, const size_t tail);

#endif
