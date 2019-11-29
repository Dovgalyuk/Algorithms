#ifndef GRAPH_H
#define GRAPH_H

// Stores int values inside
typedef size_t Data;

struct Graph;
struct Iterator;

// Creates a new Iterator
Iterator* iterator_create(Graph* graph, Data vertex);

// Deletes Iterator
void iterator_delete(Iterator* iterator);

// Creates a ected graph with N vertices
Graph* graph_create(Data size);

// Adds a vertex
void graph_addVertex(Graph* graph);

// Adds an edge between vertices
void graph_addEdge(Graph* graph, Data firstVertex, Data secondVertex);

// Removes Vertex
void graph_removeVertex(Graph* graph, Data vertex);

// Removes edge
void graph_removeEdge(Graph* graph, Data firstVertex, Data secondVertex);

// Checks for the existence of an edge between two vertices
bool graph_checkEdge(Graph* graph, Data firstVertex, Data secondVertex);

// Sets vertex weight
void graph_setVertexWeight(Graph* graph, Data vertex, Data weight);

// Returns vertex weight
Data graph_getVertexWeight(Graph* graph, Data vertex);

// Sets edge weight
void graph_setEdgeWeight(Graph* graph, Data firstVertex, Data secondVertex, Data weight);

// Returns edge weight
Data graph_getEdgeWeight(Graph* graph, Data firstVertex, Data secondVertex);

// Deletes a ected graph
void graph_delete(Graph* graph);

#endif