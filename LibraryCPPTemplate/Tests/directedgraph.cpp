//
// Created by KirilliriK on 04.10.2021.
//

#include "directedgraph.h"

int main() {
    auto graph = new DirectedGraph<bool>(4);

    graph->setVertex(0, true);

    graph->setEdge(1, 2, 1);
    graph->setEdge(3, 2, 1);
    if (!graph->isLinked(1, 2) || !graph->isLinked(3, 2)) {
        std::cout << "Invalid graph linking" << std::endl;
        graph->displayMatrix();
        return 1;
    }

    graph->removeEdge(3, 2);
    if (graph->isLinked(3, 2)) {
        std::cout << "Invalid graph remove linking" << std::endl;
        graph->displayMatrix();
        return 1;
    }

    graph->setEdge(1, 3, 1);
    graph->removeVertex(1);
    if (graph->isLinked(1, 2) || graph->isLinked(1, 3)) {
        std::cout << "Invalid graph remove vertex" << std::endl;
        graph->displayMatrix();
        return 1;
    }

    graph->displayMatrix();
    return 0;
}
