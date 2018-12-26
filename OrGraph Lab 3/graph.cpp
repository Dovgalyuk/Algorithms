#include "graph.h"
#include "vector.h"

struct Graph
{
	size_t size;			
	Vector* graph_ds;				
	Vector* weight;					
};

struct Iterator
{
	Graph* graph;
	int indexFrom;
	int indexTo;
};

void add_vertex(Graph* graph)
{
	Vector* newMatrix = vector_create();
	vector_resize(newMatrix, (graph->size + 1) * (graph->size + 1));

	Vector* newMatrixOfWeight = vector_create();
	vector_resize(newMatrixOfWeight, (graph->size + 1) * (graph->size + 1));

	size_t line = 0;

	for (size_t i = 0, j = 0; i < (graph->size + 1) * graph->size + graph->size; i++)
	{
		if (line == (graph->size + 1))
		{
			vector_set(newMatrix, i, 0);
			vector_set(newMatrixOfWeight, i, 0);
			continue;
		}
		else if (i == (graph->size + 1) * line + graph->size)
		{
			vector_set(newMatrix, i, 0);
			vector_set(newMatrixOfWeight, i, 0);
			++line;
			continue;
		}
		vector_set(newMatrix, i, vector_get(graph->graph_ds, j));
		vector_set(newMatrixOfWeight, i, vector_get(graph->weight, j));
		++j;
	}

	vector_delete(graph->graph_ds);
	vector_delete(graph->weight);
	graph->graph_ds = newMatrix;
	graph->weight = newMatrixOfWeight;
	graph->size++;
}

Iterator* iterator_create(Graph* graph, int vertex)
{
	Iterator* iterator = new Iterator;
	iterator->graph = graph;
	find_pair(iterator, vertex);
	return iterator;
}

void find_pair(Iterator* iterator, int vertex)
{
	iterator->indexFrom = vertex;
	iterator->indexTo = 0;
	next_iterator(iterator);
}

void next_iterator(Iterator* iterator)
{
	size_t indexOfArray;

	do
	{
		if (iterator->indexTo == iterator->graph->size - 1)
		{
			iterator->indexTo = -1;
			break;
		}

		iterator->indexTo++;
		indexOfArray = iterator->graph->size * iterator->indexFrom + iterator->indexTo;

	} while (vector_get(iterator->graph->graph_ds, indexOfArray) != 1);
}

int get_vertex(Iterator* iterator)
{
	return iterator->indexTo;
}

void delete_iterator(Iterator* iterator)
{
	delete iterator;
}


Graph* graph_create(size_t CountOfVertex)
{
	Graph* graph = new Graph;
	graph->size = CountOfVertex;
	graph->graph_ds = vector_create();
	graph->weight = vector_create();
	vector_resize(graph->graph_ds, CountOfVertex * CountOfVertex);
	vector_resize(graph->weight, CountOfVertex * CountOfVertex);
	return graph;
}


void delete_vertex(Graph* graph, int vertex)
{
	Vector* newMatrix = vector_create();
	vector_resize(newMatrix, (graph->size - 1) * (graph->size - 1));

	Vector* newMatrixOfWeight = vector_create();
	vector_resize(newMatrixOfWeight, (graph->size - 1) * (graph->size - 1));

	size_t line = 0;

	for (size_t i = 0, j = 0; j < (graph->size - 1) * (graph->size - 1) - 1; i++)
	{
		if (line == vertex)
		{
			if (i == graph->size * (line + 1))
			{
				++line;
				--i;
				continue;
			}
			continue;
		}
		else if (i == graph->size * line + vertex)
		{
			++line;
			continue;
		}
		vector_set(newMatrix, j, vector_get(graph->graph_ds, i));
		vector_set(newMatrixOfWeight, j, vector_get(graph->weight, i));
		++j;
	}

	vector_delete(graph->graph_ds);
	vector_delete(graph->weight);
	graph->graph_ds = newMatrix;
	graph->graph_ds = newMatrixOfWeight;
	graph->size--;
}

void add_edge(Graph* graph, int start_vertex, int end_vertex)
{
	size_t index = graph->size * start_vertex + end_vertex;
	vector_set(graph->graph_ds, index, 1);
}

void delete_edge(Graph* graph, int start_vertex, int end_vertex)
{
	size_t index = graph->size * start_vertex + end_vertex;
	vector_set(graph->graph_ds, index, 0);
	vector_set(graph->weight, index, 0);
}

bool is_edge(Graph* graph, int start_vertex, int end_vertex)
{
	size_t index = graph->size * start_vertex + end_vertex;
	return vector_get(graph->graph_ds, index);
}

void set_weight(Graph* graph, int start_vertex, int end_vertex, int weight)
{
	size_t index = graph->size * start_vertex + end_vertex;
	vector_set(graph->weight, index, weight);
}

int get_weight(Graph* graph, int start_vertex, int end_vertex)
{
	size_t index = graph->size * start_vertex + end_vertex;
	return vector_get(graph->weight, index);
}

int iterator_weight(Iterator* iterator)
{
	return vector_get(iterator->graph->weight, iterator->graph->size * iterator->indexFrom + iterator->indexTo);
}

void delete_graph(Graph* graph)
{
	vector_delete(graph->graph_ds);
	vector_delete(graph->weight);
	delete graph;
}

bool is_neighbors(Iterator* iterator)
{
	if (get_vertex(iterator) != -1) return true;
	return false;
}
