#include <limits.h>
#include <iostream>
#include "graph.h"

void printResult(int* distance, bool* isVisited, const size_t graphSize)
{
   std::cout << "Distance: " << std::endl;
   for (int i = 0; i < graphSize; i++)
      std::cout << distance[i] << " ";

   std::cout << std::endl;

   std::cout << "IsVisited: " << std::endl;
   for (int i = 0; i < graphSize; i++)
      std::cout << isVisited[i] << " ";

   std::cout << std::endl;
}

void dijkstraAlgorithm(Graph* graph, const size_t graphSize, const size_t startVertex)
{
   int distance[graphSize];
   bool isVisited[graphSize];

   for (int i = 0; i < graphSize; i++)
      distance[i] = INT_MAX, isVisited[i] = false;

   distance[startVertex] = 0;
   int currentVertex = startVertex;
   
   while (currentVertex != -1)
   {
      for (int i = 0; i < graphSize; i++)
      {
         int currentWeight = graph_getEdgeValue(graph, currentVertex, i);
         if (currentWeight && currentWeight + distance[currentVertex] < distance[i])
            distance[i] = currentWeight + distance[currentVertex];
      }

      isVisited[currentVertex] = true;
      currentVertex = -1;
      int minDist = INT_MAX;

      for (int i = 0; i < graphSize; i++)
         if (!isVisited[i] && (distance[i] < minDist))
            currentVertex = i, minDist = distance[i];
   }

   printResult(distance, isVisited, graphSize);
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
