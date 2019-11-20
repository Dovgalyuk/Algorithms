

#ifndef GRAPH_H
#define GRAPH_H

// Graph(Directed)
// Stores integer values inside
#include "defines.h"

struct Graph;
struct Vertex;
struct Edge;

// Creates new graph
Graph* graph_create(size_t vertex_count);

// Destroys the graph and frees the memory
void graph_delete(Graph* graph);

// Adds new vertex to graph
Vertex* graph_add_vertex(Graph* graph);

// Adds new edge to graph
Edge* graph_add_edge(Graph* graph, Vertex* head, const Vertex* tail);

// Removes specified vertex from graph
void graph_remove_vertex(Vertex* vertex);

// Removes specified edge from graph
void graph_remove_edge(Edge* edge);

// Returns true if there is edge directed from head to tail
bool graph_check_edge(const Vertex* head, const Vertex* tail);

// Sets specified vertex mark
void graph_set_vertex_mark(Vertex* vertex, Mark mark);

// Returns specified vertex mark
Mark graph_get_vertex_mark(Vertex* vertex);

// Sets specified edge mark
void graph_set_edge_mark(Edge* edge, Mark mark);

// Returns specified edge mark
Mark graph_get_edge_mark(Edge* edge);

#endif
