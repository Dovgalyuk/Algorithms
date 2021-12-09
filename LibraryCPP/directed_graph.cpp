#include "directed_graph.h"
#include "../LibraryCPPTemplate/array.h" //else it uses the wrong array.h

struct iterator
{
	int	CurrentNeighbor = 0;
	directed_graph* DirectedGraphPtr;
	int vertex;

	iterator(int vertex)
	{
		this->vertex = vertex;
	}
	~iterator()
	{
		DirectedGraphPtr = nullptr;
	}
};

struct directed_graph
{
	struct vertex
	{
		int label = -1;
	};

	struct edge
	{
		bool exists = 0;
		int label = -1;
	};

	typedef Array<vertex> vertex_arr;
	vertex_arr* vertex_labels;
	typedef Array<edge> matrix_arr;
	matrix_arr* matrix;
	int vertexes_amount;

	iterator* createIterator(int vertex)
	{
		iterator* iter = new iterator(vertex);
		iter->DirectedGraphPtr = this;
		return iter;
	}

	directed_graph(int vertexes_amount)
	{
		vertex_labels = new vertex_arr(vertexes_amount);
		matrix = new matrix_arr(vertexes_amount * vertexes_amount);
		this->vertexes_amount = vertexes_amount;
	}
	~directed_graph()
	{
		delete vertex_labels;
		delete matrix;
	}
};

bool NeighborListEmpty(iterator* iter)
{
	for (int i = iter->CurrentNeighbor; i < iter->DirectedGraphPtr->vertexes_amount; i++)
	{
		if (iter->DirectedGraphPtr->matrix->get((iter->vertex * iter->DirectedGraphPtr->vertexes_amount) + i).exists == 1)
			return false;
	}
	iter->CurrentNeighbor = 0;
	return true;
}

int NextNeighborIndex(iterator* iter)
{
	while (iter->DirectedGraphPtr->matrix->get((iter->vertex * iter->DirectedGraphPtr->vertexes_amount) + iter->CurrentNeighbor).exists == 0)
	{
		iter->CurrentNeighbor++;
	}
	iter->CurrentNeighbor++;
	return iter->CurrentNeighbor - 1;
}

directed_graph* create_directed_graph(int vertexes_amount)
{
	return new directed_graph(vertexes_amount);
}

void delete_iterator(iterator* iter)
{
	delete iter;
}

void delete_directed_graph(directed_graph* graph)
{
	delete graph;
}

void add_vertex(struct directed_graph* graph)
{
	typedef Array<directed_graph::vertex> vertex_arr;
	vertex_arr* vertex_labels = new vertex_arr(graph->vertexes_amount + 1);
	typedef Array<directed_graph::edge> matrix_arr;
	matrix_arr* matrix = new matrix_arr((graph->vertexes_amount + 1) * (graph->vertexes_amount + 1));
	for (int i = 0; i < graph->vertexes_amount; i++)
	{
		vertex_labels->set(i, graph->vertex_labels->get(i));
	}
	for (int i = 0, j = 0; i < graph->vertexes_amount * graph->vertexes_amount; j++)
	{
		for (int k = 0; k < graph->vertexes_amount; k++)
		{
			matrix->set(i + j, graph->matrix->get(i));
			i++;
		}
	}
	graph->matrix = matrix;
	graph->vertex_labels = vertex_labels;
	graph->vertexes_amount++;
}

void add_edge(directed_graph* graph, int vertex1, int vertex2)
{
	if ((vertex1 * graph->vertexes_amount) + vertex2 < graph->vertexes_amount * graph->vertexes_amount)
	{
		directed_graph::edge* edge = new directed_graph::edge;
		edge->label = graph->matrix->get((vertex1 * graph->vertexes_amount) + vertex2).label;
		edge->exists = 1;
		graph->matrix->set(((vertex1 * graph->vertexes_amount) + vertex2), *edge);
	}
}

void remove_vertex(struct directed_graph* graph, int vertex)
{
	if (vertex < graph->vertexes_amount && graph->vertexes_amount > 1)
	{
		typedef Array<directed_graph::vertex> vertex_arr;
		vertex_arr* vertex_labels = new vertex_arr(graph->vertexes_amount - 1);
		typedef Array<directed_graph::edge> matrix_arr;
		matrix_arr* matrix = new matrix_arr((graph->vertexes_amount - 1) * (graph->vertexes_amount - 1));
		for (int i = 0, j = 0; i < graph->vertexes_amount; i++)
		{
			if (i != vertex)
			{
				vertex_labels->set(j, graph->vertex_labels->get(i));
				j++;
			}
		}
		for (int i = 0, j = 0; i < graph->vertexes_amount * graph->vertexes_amount; i++)
		{
			if (i / graph->vertexes_amount != vertex && i - (i / graph->vertexes_amount) * graph->vertexes_amount != vertex)
			{
				matrix->set(j, graph->matrix->get(i));
				j++;
			}
		}
		graph->matrix = matrix;
		graph->vertex_labels = vertex_labels;
		graph->vertexes_amount--;
	}
}

void remove_edge(directed_graph* graph, int vertex1, int vertex2)
{
	if (vertex1 < graph->vertexes_amount && vertex2 < graph->vertexes_amount)
	{
		directed_graph::edge* edge = new directed_graph::edge;
		edge->label = graph->matrix->get((vertex1 * graph->vertexes_amount) + vertex2).label;
		edge->exists = 0;
		graph->matrix->set(((vertex1 * graph->vertexes_amount) + vertex2), *edge);
	}
}

void set_vertex_label(directed_graph* graph, int vertex_index, int vertex_label)
{
	if (vertex_index < graph->vertexes_amount)
	{
		directed_graph::vertex* vertex = new directed_graph::vertex;
		vertex->label = vertex_label;
		graph->vertex_labels->set(vertex_index, *vertex);
	}
}

void set_edge_label(directed_graph* graph, int vertex1, int vertex2, int edge_label)
{
	if (vertex1 < graph->vertexes_amount && vertex2 < graph->vertexes_amount)
	{
		directed_graph::edge* edge = new directed_graph::edge;
		edge->exists = graph->matrix->get((vertex1 * graph->vertexes_amount) + vertex2).exists;
		edge->label = edge_label;
		graph->matrix->set(((vertex1 * graph->vertexes_amount) + vertex2), *edge);
	}
}

int get_vertex_label(directed_graph* graph, int vertex_index)
{
	if (vertex_index < graph->vertexes_amount)
		return graph->vertex_labels->get(vertex_index).label;
	else
		return -1;
}

int get_edge_label(directed_graph* graph, int vertex1, int vertex2)
{
	if (vertex1 < graph->vertexes_amount && vertex2 < graph->vertexes_amount)
		return graph->matrix->get((vertex1 * graph->vertexes_amount) + vertex2).label;
	else
		return -1;
}

bool edge_exists(directed_graph* graph, int vertex1, int vertex2)
{
	return graph->matrix->get((vertex1 * graph->vertexes_amount) + vertex2).exists;
}

iterator* new_iterator(directed_graph* graph, int vertex)
{
	return graph->createIterator(vertex);
}