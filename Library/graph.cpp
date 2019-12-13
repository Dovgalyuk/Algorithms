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


static ListItem* findEdge(const Graph* graph, const size_t head, const size_t tail)
{
	ListItem* currEdgeItem = list_first(graph->vertices[head].edges);
	while (currEdgeItem != NULL)
	{
		if (list_item_data(currEdgeItem)->tail == tail)
		{
			return currEdgeItem;
		}
		currEdgeItem = list_item_next(currEdgeItem);
	}
	return NULL;
}

static void addVertices(Graph* graph, const size_t amount)
{
	Vertex* newVertices = new Vertex[graph->vertices_count + amount];
	for (size_t i = 0; i < graph->vertices_count; i++)
	{
		newVertices[i] = graph->vertices[i];
	}
	for (size_t i = 0; i < amount; i++)
	{
		newVertices[graph->vertices_count].mark = Mark();
		newVertices[graph->vertices_count].edges = list_create();
		graph->vertices_count++;
	}
	delete[] graph->vertices;
	graph->vertices = newVertices;
}

static void deleteEdges(List* edges)
{
	ListItem* edgeItem = list_first(edges);
	while (edgeItem != NULL)
	{
		delete list_item_data(edgeItem);
		edgeItem = list_item_next(edgeItem);
	}
}

Graph* graph_create(const size_t vertex_count)
{
	Graph* newGraph = new Graph();
	newGraph->vertices_count = 0;
	addVertices(newGraph, vertex_count);
	return newGraph;
}

void graph_delete(Graph* graph)
{
	for (size_t i = 0; i < graph->vertices_count; i++)
	{
		deleteEdges(graph->vertices[i].edges);
		list_delete(graph->vertices[i].edges);
	}
	delete[] graph->vertices;
	delete graph;
}

size_t graph_add_vertex(Graph* graph)
{
	addVertices(graph, 1);
	return graph->vertices_count;
}

void graph_add_edge(Graph* graph, const size_t head, const size_t tail)
{
	Edge* newEdge = new Edge();
	newEdge->mark = Mark();
	newEdge->head = head;
	newEdge->tail = tail;
	list_insert(graph->vertices[head].edges, newEdge);
}

inline static size_t decIfGrtr(size_t a, size_t b)
{
	return a > b ? a - 1 : a;
}

static void fixIndexes(Graph* graph, size_t vertex, size_t target)
{
	List* edges = graph->vertices[vertex].edges;
	ListItem* edgeItem = list_first(edges);
	while (edgeItem != NULL)
	{
		ListItem* next = list_item_next(edgeItem);
		Edge* edge = list_item_data(edgeItem);
		const size_t tail = edge->tail, head = edge->head;
		if (tail >= target || head >= target)
		{
			if (tail != target && head != target)
			{
				edge->head = tail - 1;
				edge->tail = tail - 1;
			}
			else {
				delete list_item_data(edgeItem);
				list_erase(edges, edgeItem);
			}
		}
		edgeItem = next;
	}
}

void graph_remove_vertex(Graph* graph, const size_t vertex)
{
	deleteEdges(graph->vertices[vertex].edges);
	list_delete(graph->vertices[vertex].edges);

	Vertex* newVertices = new Vertex[graph->vertices_count - 1];
	for (size_t i = 0; i < vertex; i++)
	{
		newVertices[i] = graph->vertices[i];
	}
	for (size_t i = vertex; i < graph->vertices_count - 1; i++)
	{
		newVertices[i] = graph->vertices[i + 1];
	}
	delete[] graph->vertices;
	graph->vertices_count--;
	graph->vertices = newVertices;
	for (size_t i = 0; i < graph->vertices_count; i++)
	{
		fixIndexes(graph, i, vertex);
	}
}

void graph_remove_edge(Graph* graph, const size_t head, const size_t tail)
{
	ListItem* edgeItem = findEdge(graph, head, tail);
	delete list_item_data(edgeItem);
	list_erase(graph->vertices[head].edges, edgeItem);
}

bool graph_check_edge(const Graph* graph, const size_t head, const size_t tail)
{
	return findEdge(graph, head, tail) != NULL;
}

void graph_set_vertex_mark(Graph* graph, const size_t vertex, const Mark mark)
{
	graph->vertices[vertex].mark = mark;
}

Mark graph_get_vertex_mark(const Graph* graph, const size_t vertex)
{
	return graph->vertices[vertex].mark;
}

void graph_set_edge_mark(Graph* graph, const size_t head, const size_t tail, const Mark mark)
{
	list_item_data(findEdge(graph, head, tail))->mark = mark;
}

Mark graph_get_edge_mark(const Graph* graph, const size_t head, const size_t tail)
{
	return list_item_data(findEdge(graph, head, tail))->mark;
}

Data Iterator::operator*() const {
	return list_item_data(this->curr);
}

Iterator& Iterator::operator++() {
	curr = list_item_next(this->curr);
	return *this;
}

Iterator& Iterator::operator--() {
	curr = list_item_prev(this->curr);
	return *this;
}

bool Iterator::operator==(const Iterator& rhs) const {
	return this->curr == rhs.curr;
}

bool Iterator::operator!=(const Iterator& rhs) const {
	return !(*this == rhs);
}

Iterator graph_iterator_begin(Graph* graph, size_t vertex)
{
	Iterator iter;
	iter.curr = list_first(graph->vertices[vertex].edges);
	return iter;
}

Iterator graph_iterator_end(Graph* graph, size_t vertex)
{
	Iterator iter;
	iter.curr = NULL;
	return iter;
}