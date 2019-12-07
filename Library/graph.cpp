#include "graph.h"
#include "array.h"
#include "map"

struct Graph
{
	size_t size;
	Array* graph;
	Array* weight;
};

Iterator iterator_begin(Graph* graph, Data vertex)
{
	Iterator iterator;
	iterator.graph = graph;
	iterator.firstVertex = vertex;
	iterator.secondVertex = 0;
	++iterator;
	return iterator;
}

Iterator iterator_end(Graph* graph, Data vertex)
{
	Iterator iterator;
	iterator.graph = graph;
	iterator.firstVertex = vertex;
	iterator.secondVertex = graph->size;
	return iterator;
}

Graph* graph_create(Data size)
{
	Graph* graph = new Graph;
	graph->graph = array_create(size * size);
	graph->weight = array_create(size * size);
	graph->size = size;
	return graph;
}

void graph_addVertex(Graph* graph)
{
	size_t newSize = graph->size + 1;
	Array* tempArray = array_create(newSize * newSize);
	Array* tempWeightArray = array_create(newSize * newSize);
	size_t line = 0;

	for (size_t i = 0, j = 0; i < newSize * graph->size * 2; i++)
	{
		if (line == newSize)
		{
			array_set(tempArray, i, 0);
			array_set(tempWeightArray, i, 0);
			continue;
		}
		else if (i == newSize * line + graph->size)
		{
			array_set(tempArray, i, 0);
			array_set(tempWeightArray, i, 0);
			line++;
			continue;
		}
		array_set(tempArray, i, array_get(graph->graph, j));
		array_set(tempWeightArray, i, array_get(graph->weight, j));
		j++;
	}

	array_delete(graph->graph);
	array_delete(graph->weight);
	graph->graph = tempArray;
	graph->weight = tempWeightArray;
	graph->size++;
}

void graph_addEdge(Graph* graph, Data firstVertex, Data secondVertex)
{
	size_t arrayIndex = graph->size * firstVertex + secondVertex;
	array_set(graph->graph, arrayIndex, 1);
}

void graph_removeVertex(Graph* graph, Data vertex)
{
	size_t newSize = graph->size - 1;
	Array* tempArray = array_create(newSize * newSize);
	Array* tempWeightArray = array_create(newSize * newSize);
	size_t line = 0;

	for (size_t i = 0, j = 0; j < newSize * newSize - 1; i++)
	{
		if (line == vertex)
		{
			if (i == graph->size * (line + 1))
			{
				line++;
				i--;
				continue;
			}
			continue;
		}
		else if (i == graph->size * line + vertex)
		{
			line++;
			continue;
		}
		array_set(tempArray, j, array_get(graph->graph, i));
		array_set(tempWeightArray, j, array_get(graph->weight, i));
		j++;
	}

	array_delete(graph->graph);
	array_delete(graph->weight);
	graph->graph = tempArray;
	graph->weight = tempWeightArray;
	graph->size--;
}

void graph_removeEdge(Graph* graph, Data firstVertex, Data secondVertex)
{
	size_t indexArray = graph->size * firstVertex + secondVertex;
	array_set(graph->graph, indexArray, 0);
	array_set(graph->weight, indexArray, 0);
}

bool graph_checkEdge(Graph* graph, Data firstVertex, Data secondVertex)
{
	size_t indexArray = graph->size * firstVertex + secondVertex;
	return array_get(graph->graph, indexArray) == 1;
}

void graph_setVertexWeight(Graph* graph, Data vertex, Data weight)
{
	graph_setEdgeWeight(graph, vertex, vertex, weight);
}

Data graph_getVertexWeight(Graph* graph, Data vertex)
{
	return	graph_getEdgeWeight(graph, vertex, vertex);
}

void graph_setEdgeWeight(Graph* graph, Data firstVertex, Data secondVertex, Data weight)
{
	size_t indexArray = graph->size * firstVertex + secondVertex;
	array_set(graph->weight, indexArray, weight);
}

Data graph_getEdgeWeight(Graph* graph, Data firstVertex, Data secondVertex)
{
	size_t indexArray = graph->size * firstVertex + secondVertex;
	return array_get(graph->weight, indexArray);
}

void graph_delete(Graph* graph)
{
	array_delete(graph->graph);
	array_delete(graph->weight);
	delete graph;
}

Iterator Iterator::operator++()
{
	while (!graph_checkEdge(this->graph, this->firstVertex, this->secondVertex) && this->secondVertex < this->graph->size)
	{
		this->secondVertex++;
	}
	return *this;
}

std::pair<int, int> Iterator::operator*()
{
	return std::pair<int, int>(this->secondVertex, graph_getEdgeWeight(graph, this->firstVertex, this->secondVertex));
}

bool Iterator::operator==(const Iterator& n)
{
	return (this->firstVertex == n.firstVertex && this->secondVertex == n.secondVertex && this->graph == n.graph);
}

bool Iterator::operator!=(const Iterator& n)
{
	return !this->operator==(n);
}