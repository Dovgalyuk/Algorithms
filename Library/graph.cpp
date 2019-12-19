#include <stdlib.h>
#include "list.h"
#include "graph.h"

struct Graph
{
	size_t numVertex;
	Vertex* adjList;
};

struct Vertex {
	Label mark;
	List* listOfVertex;
};

Graph* graph_create(const size_t number)
{
	Graph* graph = new Graph;
	graph->numVertex = 0;
	add_vertex(graph, number);
	return graph;
}

void graph_delete(Graph* graph)
{
	for (size_t i = 0; i < graph->numVertex; i++)
	{
		ListItem* vertexs = list_first(graph->adjList[i].listOfVertex);
		while (vertexs != NULL)
		{
			ListItem* vertex_next = list_item_next(vertexs);
			list_erase(graph->adjList[i].listOfVertex, vertexs);
			vertexs = vertex_next;
		}
		list_delete(graph->adjList[i].listOfVertex);
	}
	delete[] graph->adjList;
	delete graph;
}

void add_vertex(Graph* graph, size_t amount)
{
	Vertex* new_adjList = new Vertex[graph->numVertex + amount];
	for (size_t i = 0; i < graph->numVertex; i++)
	{
		new_adjList[i] = graph->adjList[i];
	}
	for (size_t i = 0; i < amount; i++)
	{
		new_adjList[graph->numVertex].mark = Label();
		new_adjList[graph->numVertex].listOfVertex = list_create();
		graph->numVertex++;
	}
	graph->adjList = new_adjList;
}

void add_edge(Graph* graph, const size_t from, const size_t to)
{
	Edge* new_edge = new Edge;
	new_edge->mark = Label();
	new_edge->to = to;
	list_insert(graph->adjList[from].listOfVertex, new_edge);
}

void delete_vertex(Graph* graph, const size_t number)
{
	Vertex* new_adjList = new Vertex[graph->numVertex - 1];
	for (size_t i = 0; i < number; i++)
	{
		new_adjList[i] = graph->adjList[i];
	}
	for (size_t i = number; i < graph->numVertex - 1; i++)
	{
		new_adjList[i] = graph->adjList[i + 1];
	}
	delete[] graph->adjList;
	graph->adjList = new_adjList;
	graph->numVertex--;
	for (size_t i = 0; i < graph->numVertex; i++)
	{
		delete_edge(graph, i, number);
	}
}

void delete_edge(Graph* graph, const size_t from, const size_t to)
{
	ListItem* vertexs = list_first(graph->adjList[from].listOfVertex);
	while (vertexs != NULL)
	{
		if (list_item_data(vertexs)->to == to)
		{
			ListItem* vertex_next = list_item_next(vertexs);
			delete list_item_data(vertexs);
			list_erase(graph->adjList[from].listOfVertex, vertexs);
			vertexs = vertex_next;
		}
		else
		{
			vertexs = list_item_next(vertexs);
		}
	}
}

bool check_edge(const Graph* graph, const size_t from, const size_t to)
{
	ListItem* vertexs = list_first(graph->adjList[from].listOfVertex);
	while (vertexs != NULL)
	{
		if (list_item_data(vertexs)->to == to)
		{
			return true;
		}
		vertexs = list_item_next(vertexs);
	}
	return false;
}

void add_mark_edge(Graph* graph, const size_t from, const size_t to, const Label label)
{
	ListItem* vertexs = list_first(graph->adjList[from].listOfVertex);
	while (vertexs != NULL)
	{
		if (list_item_data(vertexs)->to == to)
		{
			list_item_data(vertexs)->mark = label;
		}
		vertexs = list_item_next(vertexs);
	}
}

Label read_mark_edge(const Graph* graph, const size_t from, const size_t to) {
	ListItem* vertexs = list_first(graph->adjList[from].listOfVertex);
	while (vertexs != NULL)
	{
		if (list_item_data(vertexs)->to == to)
		{
			return list_item_data(vertexs)->mark;
		}
		vertexs = list_item_next(vertexs);
	}
}

void add_mark_vertex(Graph* graph, const size_t number, const Label label)
{
	graph->adjList[number].mark = label;
}

Label read_mark_vertex(const Graph* graph, const size_t number)
{
	return graph->adjList[number].mark;
}

Data Iterator::operator*() const {
	return list_item_data(this->vertexs);
}

Iterator& Iterator::operator++() {
	vertexs = list_item_next(this->vertexs);
	return *this;
}

Iterator& Iterator::operator--() {
	vertexs = list_item_prev(this->vertexs);
	return *this;
}

bool Iterator::operator==(const Iterator& n) const {
	return this->vertexs == n.vertexs;
}

bool Iterator::operator!=(const Iterator& n) const {
	return !(*this == n);
}

Iterator iterator_begin(Graph* graph, size_t number)
{
	Iterator iter;
	iter.vertexs = list_first(graph->adjList[number].listOfVertex);
	return iter;
}
Iterator iterator_end(Graph* graph, size_t number)
{
	Iterator iter;
	iter.vertexs = NULL;
	return iter;
}