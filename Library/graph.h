#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

typedef int Label;
typedef Edge* Data;

struct Vertex;
struct Graph;
struct Edge;
struct Iterator
{
	Data operator*() const
	{
		return list_item_data(this->vertexs);
	}
	Iterator& operator++()
	{
		vertexs = list_item_next(this->vertexs);
		return *this;
	}
	Iterator& operator--()
	{
		vertexs = list_item_prev(this->vertexs);
		return *this;
	}
	bool operator==(const Iterator& n) const
	{
		return this->vertexs == n.vertexs;
	}
	bool operator!=(const Iterator& n) const
	{
		return !(*this == n);
	}
	friend Iterator iterator_begin(Graph* graph, size_t number);
	friend Iterator iterator_end(Graph* graph, size_t number);
private:
	ListItem* vertexs;
};

Graph* graph_create(const size_t number);

void graph_delete(Graph* graph);

void add_vertex(Graph* graph);

void add_edge(Graph* graph, const size_t from, const size_t to);

void delete_vertex(Graph* graph, const size_t number);

void delete_edge(Graph* graph, const size_t from, const size_t to);

bool check_edge(const Graph* graph, const size_t from, const size_t to);

void add_mark_edge(Graph* graph, const size_t from, const size_t to, const Label label);

Label read_mark_edge(const Graph* graph, const size_t from, const size_t to);

void add_mark_vertex(Graph* graph, const size_t number, const Label label);

Label read_mark_vertex(const Graph* graph, const size_t number);

#endif
