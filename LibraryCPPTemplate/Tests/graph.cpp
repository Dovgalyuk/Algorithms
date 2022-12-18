#include <iostream>
#include "graph.h"


int main() {
    auto graph = new Graph<int, int>(10, 1);

    if (graph->getDataVertex(0) != 1) {
        std::cout << "Graph initialization is incorrect\n";
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        graph->setDataVertex(i, i);
    }

    for (int i = 0; i < 10; i++) {
        if (graph->getDataVertex(i) != i) {
            std::cout << "setDataVertex error\n";
            return 1;
        }

        std::cout << graph->getDataVertex(i) << " ";
    }
    std::cout << "\n";

    graph->addEdge(graph->getVertex(0), graph->getVertex(9), 10);

    if (!graph->checkEdge(graph->getVertex(0), graph->getVertex(9))) {
        std::cout << "Adding a edge does not work correctly\n";
        return 1;
    }

    graph->addEdge(graph->getVertex(0), graph->getVertex(9), 15);
    graph->addEdge(graph->getVertex(0), graph->getVertex(2), 35);
    graph->getEdge(graph->getVertex(0), graph->getVertex(9)).setWeight(80);

    if (graph->getWeightEdge(graph->getVertex(0), graph->getVertex(9)) != 80) {
        std::cout << "Error modifying the edge weight\n";
        return 1;
    }

    graph->removeEdge(graph->getVertex(0), graph->getVertex(9));

    if (graph->checkEdge(graph->getVertex(0), graph->getVertex(9))) {
        std::cout << "Delete a edge error\n";
        return 1;
    }

    Graph<int, int>::EdgeIterator iterator(graph->getVertex(0));

    int count = 0;

    while (*iterator != nullptr) {
        count++;
        ++iterator;
    }

    if (count != 1) {
        std::cout << "Error iterator";
        return 1;
    }

    graph->removeVertex(6);

    if (graph->sizeVertexes() != 10 - 1) {
        std::cout << "Error removeVertex\n";
        return 1;
    }

    for (int i = 0; i < 10 - 1; i++) {
        std::cout << graph->getDataVertex(i) << " ";
    }

    std::cout << std::endl;
    
}
