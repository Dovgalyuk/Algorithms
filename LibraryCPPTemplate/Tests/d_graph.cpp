#include <iostream>
#include "d_graph.h"

int main() {
    int amount = 10;
    auto graph = DirectedGraph<int, int>(amount, 1);
    for (int i = 0; i < amount; ++i) {
        graph.getVertex(i)->data = i;
    }

    for (int i = 0; i < amount; ++i) {
        if (graph.getVertex(i)->data != i) {
            std::cout << "Adding a vertex to the graph does not work correctly.";
            return 1;
        }
    }

    graph.addEdge(graph.getVertex(0), graph.getVertex(3), 5);

    if (!graph.containsEdgeBetweenVertices(graph.getVertex(0), graph.getVertex(3))) {
        std::cout << "Adding a edge to the graph does not work correctly.";
        return 1;
    }

    graph.addEdge(graph.getVertex(0), graph.getVertex(2), 10);

    if (!graph.containsEdgeBetweenVertices(graph.getVertex(0), graph.getVertex(3)) ||
        !graph.containsEdgeBetweenVertices(graph.getVertex(0), graph.getVertex(2))) {
        std::cout << "Adding a edge to the graph does not work correctly.";
        return 1;
    }

    if (graph.getVertex(6)->data != 6) {
        std::cout << "Modifying the vertex data does not work correctly.";
        return 1;
    }
    graph.getVertex(6)->data = 15;
    if (graph.getVertex(6)->data != 15) {
        std::cout << "Modifying the vertex data does not work correctly.";
        return 1;
    }

    if (graph.getEdge(graph.getVertex(0), graph.getVertex(2))->data != 10) {
        std::cout << "Modifying the edge weight does not work correctly.";
        return 1;
    }
    graph.getEdge(graph.getVertex(0), graph.getVertex(2))->data = 14;
    if (graph.getEdge(graph.getVertex(0), graph.getVertex(2))->data != 14) {
        std::cout << "Modifying the edge weight does not work correctly.";
        return 1;
    }

    graph.removeEdge(graph.getVertex(0), graph.getVertex(2));
    if (!graph.containsEdgeBetweenVertices(graph.getVertex(0), graph.getVertex(3)) ||
        graph.containsEdgeBetweenVertices(graph.getVertex(0), graph.getVertex(2))) {
        std::cout << "Adding a edge to the graph does not work correctly.";
        return 1;
    }

    graph.addEdge(graph.getVertex(0), graph.getVertex(1), 10);
    graph.addEdge(graph.getVertex(0), graph.getVertex(4), 10);
    graph.addEdge(graph.getVertex(0), graph.getVertex(7), 10);
    graph.addEdge(graph.getVertex(0), graph.getVertex(9), 10);
    graph.addEdge(graph.getVertex(1), graph.getVertex(0), 10);
    graph.addEdge(graph.getVertex(3), graph.getVertex(0), 10);

    auto iterator = graph.getNearVertexIterator(graph.getVertex(0));
    int count = 0;
    while (*iterator) {
        count++;
        iterator++;
    }

    if (count != 5) {
        std::cout << "The near vertex iterator does not work correctly.";
        return 1;
    }

    auto* first = graph.getVertex(0);
    graph.removeVertex(first);

    if (graph.getVertex(0)->data != 1) {
        std::cout << "Removing vertices does not work correctly.";
        return 1;
    }

    iterator = graph.getNearVertexIterator(graph.getVertex(0));
    count = 0;
    while (*iterator) {
        count++;
        iterator++;
    }

    if (count > 0) {
        std::cout << "Removing vertices does not work correctly.";
        return 1;
    }

    iterator = graph.getNearVertexIterator(graph.getVertex(2));
    count = 0;
    while (*iterator) {
        count++;
        iterator++;
    }

    if (count > 0) {
        std::cout << "Removing vertices does not work correctly.";
        return 1;
    }

    return 0;
}