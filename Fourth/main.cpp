#include <iostream>
#include "graph.h"
#include <queue>
#include "queue.h"

struct lengthAndUsed {
    int length = 0;
    bool used = false;
};

void fill(Graph<lengthAndUsed,bool>* graph, const int vertexAmount) {
    for (int i = 0; i < vertexAmount; ++i) {
        graph->addVertex(lengthAndUsed());
    }
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
    auto* graph = new Graph<lengthAndUsed,bool>(vertexAmount, lengthAndUsed());
    fill(graph, vertexAmount);
    // две вершины 
    int firstVertexIndex = 0;
    int secondVertexIndex = 4;
    auto* first = graph->getVertex(firstVertexIndex);
    auto* second = graph->getVertex(secondVertexIndex);

    std::queue <size_t> queue;
    queue.push(firstVertexIndex);
    first->data.used = true;
    while (!queue.empty()) {
        int index = queue.front();
        queue.pop();
        auto graphIt = graph->getIterator(index);
        while((*graphIt) != nullptr) {
            if ((*graphIt) == second) {
                if (second->data.length < 1) {
                    second->data.length = graph->getVertex(index)->data.length + 1;
                }
            } 
            else if ((*graphIt)->data.used == false) {
                queue.push((graphIt.getIndex()));
                (*graphIt)->data.length =  graph->getVertex(index)->data.length + 1;
            }
            (*graphIt)->data.used = true;
            graphIt++;
        }
    }
    if (second->data.length < 1) {
	    std::cout << "No path"<< std::endl;
        return 0;
    }
    std::cout<<"min length = "<< second->data.length<< std::endl;
    delete graph;
    return 0;
}