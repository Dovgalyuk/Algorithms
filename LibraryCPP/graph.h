#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include "array.h"

// Graph data structure
// Contains the adjacency matrix and its size
struct Graph;

// Graph iterator
// Required for graph traversal
// Contains a pointer to the graph and the current edge
struct Iterator;

/* === Graph iterator functions === */

// Create graph iterator
Iterator* iterator_create(Graph* graph, size_t fromVertex);

// Returns the weight of the current edge
Data iterator_getWeight(Iterator* graphIterator);

// Selects the next edge of the current vertex
void iterator_nextEdge(Iterator* graphIterator);

// Selects the next vertex along the edge
void iterator_nextVertex(Iterator* graphIterator);

// Returns the index of the selected edge of the current vertex
size_t iterator_getEdgeIndex(Iterator* graphIterator);

// Selects the first edge that exists at the index
void iterator_selectFirstEdge(Iterator* graphIterator);

// Selects the specified edge by its index
void iterator_selectEdge(Iterator* graphIterator, size_t vertex);

// Selects the specified vertex by its index
void iterator_selectVertex(Iterator* graphIterator, size_t vertex);

// Returns the number of existing edges at the current vertex
size_t iterator_edgeCount(Iterator* graphIterator);

// Checks if the end is reached
bool iterator_edgeIsExist(Iterator* graphIterator);

// Returns the number of the current vertex
size_t iterator_getVertexIndex(Iterator* graphIterator);

// Delete graph iterator, free memory
void iterator_delete(Iterator* graphIterator);

/* === Graph functions === */

// Create graph
Graph* graph_create(const size_t size);

// Adds a new vertex
void graph_addVertex(Graph* graph);

// Adds a new edge
void graph_addEdge(Graph* graph, size_t fromVertex, size_t toVertex);

// Deletes the specified vertex
void graph_removeVertex(Graph* graph, size_t vertex);

// Deletes the specified edge
void graph_removeEdge(Graph* graph, size_t fromVertex, size_t toVertex);

// Checks whether an edge exists
bool graph_edgeIsExist(Graph* graph, size_t fromVertex, size_t toVertex);

// Changes the weight of the specified edge
void graph_setEdgeValue(Graph* graph, size_t fromVertex, size_t toVertex, Data data);

// Returns the weight of the specified edge
Data graph_getEdgeValue(Graph* graph, size_t fromVertex, size_t toVertex);

// Changes the weight of the specified vertex
void graph_setVertexValue(Graph* graph, size_t vertex, Data data);

// Returns the weight of the specified vertex
Data graph_getVertexValue(Graph* graph, size_t vertex);

// Delete graph, free memory
void graph_delete(Graph* graph);

#endif
