#include <iostream>
#include "graph.h"

typedef Graph<int> MyGraph;

int main() {
    size_t vertex_count = 9;
    MyGraph graph(vertex_count, 1);

    if (graph.getVertexAmount() != 9) {
        std::cout << "Invalid vertex amount\n";
        return 1;
    }

    for (size_t i = 0; i < vertex_count; i++) {
        graph.getVertex(i).setVertexData(static_cast<int>(i));
    }

    for (size_t i = 0; i < vertex_count; i++) {
        if (graph.getVertex(i).getVertexData() != static_cast<int>(i)) {
            std::cout << "Invalid vertex data\n";
            return 1;
        }
    }

    graph.addEdge(0, 3, 15);
    graph.addEdge(2, 1, 3);
    graph.addEdge(3, 4, 5);

    if (!graph.isEdgeExist(2, 1)) {
        std::cout << "Invalid edge creation\n";
        return 1;
    }

    auto it = graph.getIterator(0);
    while (*it != static_cast<size_t>(-1)) {
        if (graph.getVertex(*it).getVertexData() != 3) {
            std::cout << "Invalid iteration\n";
            return 1;
        }
        ++it;
    }

    if (graph.getEdge(2, 1).getEdgeData() != 3) {
        std::cout << "Invalid edge data\n";
        return 1;
    }

    graph.getEdge(0, 3).setEdgeData(30);
    if (graph.getEdge(0, 3).getEdgeData() != 30) {
        std::cout << "Invalid edge data setting\n";
        return 1;
    }

    graph.removeEdge(2, 1);
    if (graph.isEdgeExist(2, 1)) {
        std::cout << "Invalid edge deletion\n";
        return 1;
    }

    graph.removeVertex(3);
    if (graph.getVertexAmount() != 8) {
        std::cout << "Invalid vertex deletion\n";
        return 1;
    }

    return 0;
}
