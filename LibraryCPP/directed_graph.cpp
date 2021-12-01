#include <C:\Users\vasill\source\repos\mendeleev8\mendeleev8\directed_graph.h>

directed_graph* create_directed_graph(int vertexes_amount)
{
	return new directed_graph(vertexes_amount);
}

void delete_directed_graph(directed_graph* graph)
{
	delete graph;
}

void add_vertex(struct directed_graph** graph)
{
	directed_graph* new_graph = new directed_graph((*graph)->vertexes_amount + 1);
	for (int i = 0; i < (*graph)->vertexes_amount; i++)
	{
		new_graph->vertex_labels[i].label = (*graph)->vertex_labels[i].label;
	}
	for (int i = 0, j = 0; i < (*graph)->vertexes_amount * (*graph)->vertexes_amount; j++)
	{
		for (int k = 0; k < (*graph)->vertexes_amount; k++)
		{
			new_graph->matrix[i + j].label = (*graph)->matrix[i].label;
			new_graph->matrix[i + j].exists = (*graph)->matrix[i].exists;
			i++;
		}
	}
	delete* graph;
	*graph = new_graph;
}

void add_edge(directed_graph* graph, int vertex1, int vertex2)
{
	if ((vertex1 * graph->vertexes_amount) + vertex2 < graph->vertexes_amount * graph->vertexes_amount)
		graph->matrix[(vertex1 * graph->vertexes_amount) + vertex2].exists = 1;
}

void remove_vertex(struct directed_graph** graph, int vertex)
{
	if (vertex < (*graph)->vertexes_amount && (*graph)->vertexes_amount > 1)
	{
		directed_graph* new_graph = new directed_graph((*graph)->vertexes_amount - 1);
		for (int i = 0, j = 0; i < (*graph)->vertexes_amount; i++)
		{
			if (i != vertex)
			{
				new_graph->vertex_labels[j].label = (*graph)->vertex_labels[i].label;
				j++;
			}
		}
		for (int i = 0, j = 0; i < (*graph)->vertexes_amount * (*graph)->vertexes_amount; i++)
		{
			if (i / (*graph)->vertexes_amount != vertex && i - (i / (*graph)->vertexes_amount) * (*graph)->vertexes_amount != vertex)
			{
				new_graph->matrix[j].label = (*graph)->matrix[i].label;
				new_graph->matrix[j].exists = (*graph)->matrix[i].exists;
				j++;
			}
		}
		delete* graph;
		*graph = new_graph;
	}
}

void remove_edge(directed_graph* graph, int vertex1, int vertex2)
{
	if (vertex1 < graph->vertexes_amount && vertex2 < graph->vertexes_amount)
		graph->matrix[(vertex1 * graph->vertexes_amount) + vertex2].exists = 0;
}

void set_vertex_label(directed_graph* graph, int vertex_index, int vertex_label)
{
	if (vertex_index < graph->vertexes_amount)
		graph->vertex_labels[vertex_index].label = vertex_label;
}

void set_edge_label(directed_graph* graph, int vertex1, int vertex2, int edge_label)
{
	if (vertex1 < graph->vertexes_amount && vertex2 < graph->vertexes_amount)
		graph->matrix[(vertex1 * graph->vertexes_amount) + vertex2].label = edge_label;
}

int get_vertex_label(directed_graph* graph, int vertex_index)
{
	if (vertex_index < graph->vertexes_amount)
		return graph->vertex_labels[vertex_index].label;
	else
		return -1;
}

int get_edge_label(directed_graph* graph, int vertex1, int vertex2)
{
	if (vertex1 < graph->vertexes_amount && vertex2 < graph->vertexes_amount)
		return graph->matrix[(vertex1 * graph->vertexes_amount) + vertex2].label;
	else
		return -1;
}

bool edge_exists(directed_graph* graph, int vertex1, int vertex2)
{
	return graph->matrix[(vertex1 * graph->vertexes_amount) + vertex2].exists;
}

directed_graph::iterator* new_iterator(directed_graph* graph)
{
	return graph->createIterator();
}