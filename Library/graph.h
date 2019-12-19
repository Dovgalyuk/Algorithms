#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include "defines.h"

struct Vertex;
struct Graph;
struct  Iterator {
	Data operator*() const;
	Iterator& operator++();
	Iterator& operator--();
	bool operator==(const Iterator& n) const;
	bool operator!=(const Iterator& n) const;
	friend Iterator iterator_begin(Graph* graph, size_t number);
	friend Iterator iterator_end(Graph* graph, size_t number);

private:
	ListItem* vertexs;
};

Graph* graph_create(const size_t number);

void graph_delete(Graph* graph);

void add_vertex(Graph* graph, size_t amount = 1);

void add_edge(Graph* graph, const size_t from, const size_t to);

void delete_vertex(Graph* graph, const size_t number);

void delete_edge(Graph* graph, const size_t from, const size_t to);

bool check_edge(const Graph* graph, const size_t from, const size_t to);

void add_mark_edge(Graph* graph, const size_t from, const size_t to, const Label label);

Label read_mark_edge(const Graph* graph, const size_t from, const size_t to);

void add_mark_vertex(Graph* graph, const size_t number, const Label label);

Label read_mark_vertex(const Graph* graph, const size_t number);

#endif
