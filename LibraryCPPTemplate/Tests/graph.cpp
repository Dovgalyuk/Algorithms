#include <iostream>
#include "graph.h"

typedef Graph<int> MyGraph;

int main() {
    size_t vertex_count = 6;
    MyGraph* graph = new MyGraph(vertex_count, 1);

    if (graph->getVertexAmount() != 6) {
        std::cout << "Invalid vertex amount\n";
        return 1;
    }

    for (size_t i = 0; i < vertex_count; i++) {
        graph->getVertex(i)->setVertexData(static_cast<int>(i));
    }

    for (size_t i = 0; i < vertex_count; i++) {
        if (graph->getVertex(i)->getVertexData() != static_cast<int>(i)) {
            std::cout << "Invalid vertex data\n";
            return 1;
        }
    }

    graph->addEdge(2, 1, 15);
    graph->addEdge(0, 3, 3);
    graph->addEdge(6, 3, 2);
    graph->addEdge(5, 4, 20);
    graph->addEdge(7, 8, 3);
    graph->addEdge(0, 2, 6);

    if (!graph->isEdgeExist(2, 1)) {
        std::cout << "Invalid edge creation\n";
        return 1;
    }

    auto it = graph->getIterator(0);
    size_t visitedCount = 0;
        while (*it != nullptr) {
    
        if ((*it)->getVertexData() != 3) {
            std::cout << "Invalid vertex data\n";
            return 1;
        }

    
        if (visitedCount > 0 && !graph->isEdgeExist(it.getEnd(), it.getEnd() + 1)) {
            std::cout << "Vertices are not adjacent\n";
            return 1;
        }

    
        ++it;
        ++visitedCount;
    }


    if (visitedCount != graph->getVertexAmount()) {
        std::cout << "Not all vertices were visited\n";
        return 1;
    }

    std::cout << "Iterator test passed\n";
    return 0;

    if (graph->getEdge(2, 1)->getEdgeData() != 15) {
        std::cout << "Invalid edge data\n";
        return 1;
    }

    graph->getEdge(0, 3)->setEdgeData(30);
    if (graph->getEdge(0, 3)->getEdgeData() != 30) {
        std::cout << "Invalid edge data setting\n";
        return 1;
    }

    graph->removeEdge(2, 1);
    if (graph->isEdgeExist(2, 1)) {
        std::cout << "Invalid edge deletion\n";
        return 1;
    }

    graph->removeVertex(3);
    if (graph->getVertexAmount() != 4) {
        std::cout << "Invalid vertex deletion\n";
        return 1;
    }

    delete graph;
}