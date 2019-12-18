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

struct Edge {
	Label mark;
	size_t to;
};

Graph* graph_create(const size_t number)
{
	Graph* graph = new Graph;
	graph->numVertex = 0;
	for (size_t i = 0; i < number; i++)
	{
		add_vertex(graph);
	}
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

void add_vertex(Graph* graph)
{
	Vertex* new_adjList = new Vertex[graph->numVertex + 1];
	for (size_t i = 0; i < graph->numVertex; i++)
	{
		new_adjList[i] = graph->adjList[i];
	}
	new_adjList[graph->numVertex].listOfVertex = list_create();
	graph->numVertex++;
	delete[] graph->adjList;
	graph->adjList = new_adjList;
}

void add_edge(Graph* graph, const size_t from, const size_t to)
{
	Edge* new_edge = new Edge;
	new_edge->to = to;
	list_insert(graph->adjList[from].listOfVertex, new_edge);
}

void delete_vertex(Graph* graph, const size_t number)
{
	ListItem* vertexs = list_first(graph->adjList[number].listOfVertex);
	while (vertexs != NULL)
	{
		list_erase(graph->adjList[number].listOfVertex, vertexs);
		vertexs = list_item_next(vertexs);
	}
	list_delete(graph->adjList[number].listOfVertex);
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
			list_erase(graph->adjList[from].listOfVertex, vertexs);
			vertexs = vertex_next;
		}
		vertexs = list_item_next(vertexs);
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