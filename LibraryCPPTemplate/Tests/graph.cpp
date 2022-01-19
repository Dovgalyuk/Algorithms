#include <iostream>
#include "graph.h"

int main() {

    int numberVertexes = 10;

    auto graph = new Graph<int>(numberVertexes, 1);

    for (size_t i = 0; i < numberVertexes; i++) {
        if (graph->getDataVertex(i) != 1) {
            std::cout << "Graph initialization is incorrect\n";
            return 1;
        }
    }

    for (int i = 0; i < numberVertexes; i++) {
        graph->setDataVertex(i, i);
    }

    for (int i = 0; i < numberVertexes; i++) {
        if (graph->getDataVertex(i) != i) {
            std::cout << "setDataVertex error\n";
            return 1;
        }

        std::cout << graph->getDataVertex(i) << " ";
    }

    std::cout << std::endl;

    graph->addEdge(graph->getVertex(0), graph->getVertex(5), 10);

    if (!graph->checkEdge(graph->getVertex(0), graph->getVertex(5))) {
        std::cout << "Adding a edge does not work correctly.";
        return 1;
    }

    graph->addEdge(graph->getVertex(0), graph->getVertex(3), 5);

    if (!graph->checkEdge(graph->getVertex(0), graph->getVertex(3)) || graph->getWeightEdge(graph->getVertex(0), graph->getVertex(3)) != 5) {
        std::cout << "Adding a edge does not work correctly.";
        return 1;
    }

    graph->addEdge(graph->getVertex(0), graph->getVertex(9), 15);
    graph->addEdge(graph->getVertex(0), graph->getVertex(2), 35);

    graph->setWeightEdge(graph->getVertex(0), graph->getVertex(9), 80);

    if (graph->getWeightEdge(graph->getVertex(0), graph->getVertex(9)) != 80) {
        std::cout << "Error modifying the edge weight\n";
        return 1;
    }

    graph->removeEdge(graph->getVertex(0), graph->getVertex(9));

    if (graph->checkEdge(graph->getVertex(0), graph->getVertex(9))) {
        std::cout << "Delete a edge error\n";
        return 1;
    }

    Graph<int>::EdgeIterator iterator(graph->getVertex(0));

    int count = 0;

    while (iterator.hasNext()) {
        count++;
        ++iterator;
    }

    if (count != 3) {
        std::cout << "Error iterator";
        return 1;
    }

    graph->removeVertex(6);

    if (graph->sizeVertexex() != numberVertexes - 1) {
        std::cout << "Error removeVertex\n";
        return 1;
    }

    for (int i = 0; i < numberVertexes - 1; i++) {
        std::cout << graph->getDataVertex(i) << " ";
    }

    std::cout << std::endl;

    delete graph;
}
