
#pragma once
#include "graph.h"
#include "list.h"

struct Graph {
	Vertex* vertices;
	size_t vertices_count;
};

struct Vertex {
	List* edges;
	Mark mark;
};

struct  Graph_iterator {
	Data operator*() const {
		return list_item_data(this->curr);
	}

	Graph_iterator& operator++() {
		curr = list_item_next(this->curr);
		return *this;
	}

	Graph_iterator& operator--() {
		curr = list_item_prev(this->curr);
		return *this;
	}

	bool operator==(const Graph_iterator& rhs) const {
		return this->curr == rhs.curr;
	}

	bool operator!=(const Graph_iterator& rhs) const {
		return !(*this == rhs);
	}

	friend Graph_iterator graph_iterator_begin(Graph* graph, size_t vertex);
	friend Graph_iterator graph_iterator_end(Graph* graph, size_t vertex);
private:
	ListItem* curr;
};

Graph_iterator graph_iterator_begin(Graph* graph, size_t vertex)
{
	Graph_iterator iter;
	iter.curr = list_first(graph->vertices[vertex].edges);
	return iter;
}

Graph_iterator graph_iterator_end(Graph* graph, size_t vertex)
{
	Graph_iterator iter;
	iter.curr = NULL;
	return iter;
}
