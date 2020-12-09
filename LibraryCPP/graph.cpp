#include "graph.h"

struct Graph
{
   size_t size;
   Array* adjacencyMatrix;
};

struct Iterator
{
   Graph* graph;
   size_t fromVertex;
   size_t toVertex;
};

/* === Graph iterator functions implement  === */

Iterator* iterator_create(Graph* graph, size_t fromVertex)
{
   Iterator* graphIterator = new Iterator;
   graphIterator->graph = graph;
   graphIterator->fromVertex = fromVertex;
   graphIterator->toVertex = 0;
   iterator_nextEdge(graphIterator);
   return graphIterator;
}

Data iterator_getWeight(Iterator* graphIterator)
{
   return graph_getEdgeValue(graphIterator->graph, graphIterator->fromVertex, graphIterator->toVertex);
}

size_t iterator_getVertexIndex(Iterator* graphIterator)
{
   return graphIterator->fromVertex;
}

size_t iterator_getEdgeIndex(Iterator* graphIterator)
{
   return graphIterator->toVertex;
}

void iterator_nextEdge(Iterator* graphIterator)
{
   for (int i = graphIterator->toVertex + 1; i < graphIterator->graph->size; i++)
   {
      if (graph_edgeIsExist(graphIterator->graph, graphIterator->fromVertex, i))
      {
         graphIterator->toVertex = i;
         return;
      }
   }
   graphIterator->toVertex = 0;
}

void iterator_nextVertex(Iterator* graphIterator)
{
   graphIterator->fromVertex = graphIterator->toVertex;
   graphIterator->toVertex = 0;
   iterator_nextEdge(graphIterator);
}

void iterator_selectFirstEdge(Iterator* graphIterator)
{
   graphIterator->toVertex = 0;
   if (iterator_edgeIsExist(graphIterator))
      return;
   else
      iterator_nextEdge(graphIterator);
}

void iterator_selectEdge(Iterator* graphIterator, size_t vertex)
{
   if (graph_edgeIsExist(graphIterator->graph, graphIterator->fromVertex, vertex))
   {
      iterator_selectFirstEdge(graphIterator);
      while (iterator_getEdgeIndex(graphIterator) != vertex)
         iterator_nextEdge(graphIterator);
   }
}

bool iterator_edgeIsExist(Iterator* graphIterator)
{
   return graph_edgeIsExist(graphIterator->graph, graphIterator->fromVertex, graphIterator->toVertex);
}

size_t iterator_edgeCount(Iterator* graphIterator)
{
   size_t count = 0;
   for (size_t i = 0; i < graphIterator->graph->size; i++)
      if (graph_edgeIsExist(graphIterator->graph, graphIterator->fromVertex, i))
         count++;
   return count;
}

void iterator_delete(Iterator* graphIterator)
{
   delete graphIterator;
}

/* === Graph functions implement === */

Graph* graph_create(size_t size)
{
   Graph* graph = new Graph;
   graph->size = size;
   graph->adjacencyMatrix = array_create(size * size);
   return graph;
}

void graph_addVertex(Graph* graph)
{
   size_t newSize = graph->size + 1;
   Array* newAdjacencyMatrix = array_create(newSize * newSize);

   for (int i = 0, j = 0, k = 0; i < newSize * newSize; i++)
   {
      if (i == newSize * (k + 1))
         array_set(newAdjacencyMatrix, i, 0), k++;
      else if (i >= newSize * newSize - newSize)
         array_set(newAdjacencyMatrix, i, 0);
      else
         array_set(newAdjacencyMatrix, i, array_get(graph->adjacencyMatrix, j)), j++;
   }

   array_delete(graph->adjacencyMatrix);

   graph->size = newSize;
   graph->adjacencyMatrix = newAdjacencyMatrix;
}

void graph_addEdge(Graph* graph, size_t fromVertex, size_t toVertex)
{
   array_set(graph->adjacencyMatrix, graph->size * fromVertex + toVertex, 1);
}

void graph_removeVertex(Graph* graph, size_t vertex)
{
   size_t newSize = graph->size - 1;
   Array* newAdjacencyMatrix = array_create(newSize * newSize);

   for (int i = 0, j = 0, k = 0; i < graph->size * graph->size; i++)
   {
      if (i == j * graph->size + vertex)
         j++;
      else if (i >= vertex * graph->size && i < vertex * graph->size + graph->size)
         k++;
      else
         array_set(newAdjacencyMatrix, i - j - k, array_get(graph->adjacencyMatrix, i));
   }

   array_delete(graph->adjacencyMatrix);

   graph->size = newSize;
   graph->adjacencyMatrix = newAdjacencyMatrix;
}

void graph_removeEdge(Graph* graph, size_t fromVertex, size_t toVertex)
{
   array_set(graph->adjacencyMatrix, graph->size * fromVertex + toVertex, 0);
}

bool graph_edgeIsExist(Graph* graph, size_t fromVertex, size_t toVertex)
{
   return array_get(graph->adjacencyMatrix, graph->size * fromVertex + toVertex);
}

void graph_setEdgeValue(Graph* graph, size_t fromVertex, size_t toVertex, Data data)
{
   array_set(graph->adjacencyMatrix, graph->size * fromVertex + toVertex, data);
}

Data graph_getEdgeValue(Graph* graph, size_t fromVertex, size_t toVertex)
{
   return array_get(graph->adjacencyMatrix, graph->size * fromVertex + toVertex);
}

void graph_setVertexValue(Graph* graph, size_t vertex, Data data)
{
   array_set(graph->adjacencyMatrix, graph->size * vertex + vertex, data);
}

Data graph_getVertexValue(Graph* graph, size_t vertex)
{
   return array_get(graph->adjacencyMatrix, graph->size * vertex + vertex);
}

void graph_delete(Graph* graph)
{
   array_delete(graph->adjacencyMatrix);
   delete graph;
}
