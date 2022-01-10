#include "graph.h"
#include <iostream>

int main() {
    int VertexNumber = 10;
    Graph<int>* graph = new Graph<int>(VertexNumber);

    if (graph->getVertex(0)->getData() != 0) {
        std::cout << "creating error\n";
        return 1;
    }
    else  std::cout << "graph created\n";


    for (int i = 0; i < VertexNumber; i++) {
        graph->getVertex(i)->setData(3);
        if (graph->getVertex(i)->getData() != 3) {
            std::cout << "initialization error\n";
            return 2;
        }
    }
    std::cout << "initialization runs successfully\n";

    graph->getVertex(0)->setData(1);
    if (graph->getVertex(0)->getData() != 1) {
        std::cout << "set data error\n";
        return 3;
    }
    else std::cout << "set data successfully\n";

    graph->addEdgeFromTo(0, 1);
    if (!graph->isEdgeExists(0, 1)) {
        std::cout << "edge error";
        return 4;
    }
    else std::cout << "edge added successfully\n";


    if (graph->isEdgeExists(0, 2)) {
        std::cout << "edge error";
        return 5;
    }

    graph->removeEdgeFromTo(0, 1);
    if (graph->isEdgeExists(0, 1)) {
        std::cout << "deletion error";
        return 6;
    }
    else std::cout << "deletion successfull\n";

    graph->addEdgeFromTo(1, 5);
    graph->addEdgeFromTo(1, 6);
    graph->addEdgeFromTo(1, 7);

    Graph<int>::EdgesIterator iterator(graph->getVertex(1));
    while (*iterator != nullptr) {
        std::cout << (*iterator)->getDest()->getData() << " ";
        ++iterator;
    }
    std::cout << "iterator runs succsesfully\n";
}