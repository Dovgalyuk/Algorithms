#include <limits.h>
#include <iostream>
#include "graph.h"

void printResult(Graph* graph, bool* isVisited, const size_t graphSize)
{
   std::cout << "Distance: " << std::endl;
   for (int i = 0; i < graphSize; i++)
      std::cout << graph_getVertexValue(graph, i) << " ";

   std::cout << std::endl;

   std::cout << "IsVisited: " << std::endl;
   for (int i = 0; i < graphSize; i++)
      std::cout << isVisited[i] << " ";

   std::cout << std::endl;
}

void dijkstraAlgorithm(Graph* graph, const size_t graphSize, const size_t startVertex)
{
   bool isVisited[graphSize];

   for (int i = 0; i < graphSize; i++)
   {
      graph_setVertexValue(graph, i, INT_MAX);
      isVisited[i] = false;
   }

   graph_setVertexValue(graph, startVertex, 0);
   int currentVertex = startVertex;

   Iterator* iter = iterator_create(graph, startVertex);
   while (currentVertex != -1)
   {
      while (iterator_edgeIsExist(iter))
      {
         int currentWeight = iterator_getWeight(iter);
         int currentEdge = iterator_getEdgeIndex(iter);

         if (currentWeight + graph_getVertexValue(graph, currentVertex) < graph_getVertexValue(graph, currentEdge))
            graph_setVertexValue(graph, currentEdge, currentWeight + graph_getVertexValue(graph, currentVertex));
         
         iterator_nextEdge(iter);
      }

      isVisited[currentVertex] = true;
      currentVertex = -1;
      int minDist = INT_MAX;

      for (int i = 0; i < graphSize; i++)
      {
         if (!isVisited[i] && (graph_getVertexValue(graph, i) < minDist))
         {
            currentVertex = i;
            minDist = graph_getVertexValue(graph, i);
         }
      }
      iterator_selectVertex(iter, currentVertex);
   }
   iterator_delete(iter);
   
   printResult(graph, isVisited, graphSize);
}

int main()
{
   size_t graphSize;

   std::cout << "Enter graph size: ";
   std::cin >> graphSize;
   std::cout << "Now you can enter edges: " << std::endl;

   Graph* graph = graph_create(graphSize);

   while (true)
   {
      Data fromVertex;
      Data toVertex;
      Data edgeWeight;

      std::cin >> fromVertex;
      if (fromVertex < 0)
         break;     
      std::cin >> toVertex;
      std::cin >> edgeWeight;

      graph_setEdgeValue(graph, fromVertex, toVertex, edgeWeight);
   }

   dijkstraAlgorithm(graph, graphSize, 0);

   graph_delete(graph);
   
   return 0;
}
