#include <iostream>
#include "graph.h"
#include <queue>
#include "queue.h"

void fillGraph(Graph<bool,bool>* graph, int vertexAmount) {
    graph->addEdge(0,1);
    graph->addEdge(0,2);
    graph->addEdge(1,4);
    graph->addEdge(1,3);
    graph->addEdge(2,5);
    graph->addEdge(2,1);
    graph->addEdge(5,4);
}

int main() {
    const int vertexAmount = 6;
    auto* graph = new Graph<bool,bool>(vertexAmount, false);
    fillGraph(graph, vertexAmount);
    // две вершины 
    int firstVertexIndex = 0;
    int secondVertexIndex = 4;
    auto* first = graph->getVertex(firstVertexIndex);
    auto* second = graph->getVertex(secondVertexIndex);

    Queue<int> queue2;
    std::queue <size_t> queue;
    int lengths[vertexAmount] = {};
    queue.push(firstVertexIndex);
    graph->setVertexData(firstVertexIndex, true);
    while (!queue.empty()) {
        int index = queue.front();
        queue.pop();
        auto graphIt = graph->getIterator(index);
        while((*graphIt) != nullptr) {
            if ((*graphIt) == second) {
                if (lengths[secondVertexIndex] < 1) {
                    lengths[secondVertexIndex] = lengths[index] + 1;
                }
            } 
            else if (graph->getData(graphIt.getIndex()) == false) {
                queue.push((graphIt.getIndex()));
                lengths[graphIt.getIndex()] = lengths[index] +1;
            }
            graph->setVertexData(graphIt.getIndex(), true);
            graphIt++;
        }
    }
    if (lengths[secondVertexIndex] < 1) {
	    std::cout << "No path"<< std::endl;
        return 0;
    }
    std::cout<<"min length = "<< lengths[secondVertexIndex]<< std::endl;
    delete graph;
    return 0;
}