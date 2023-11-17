#include <iostream>
#include "graph.h"

typedef Graph<int, int> MyGraph;

int main() {
    MyGraph graph;

    // Тестирование добавления вершин
    auto v1 = graph.addVertex(1);
    auto v2 = graph.addVertex(2);
    auto v3 = graph.addVertex(3);

    if (graph.vertexCount() != 3) {
        std::cout << "Error in addVertex or vertexCount\n";
        return 1;
    }

    // Тестирование добавления рёбер
    auto e1 = graph.addEdge(v1, v2, 10);
    graph.addEdge(v2, v3, 20);

    if (!graph.edgeExists(v1, v2) || !graph.edgeExists(v2, v3)) {
        std::cout << "Error in addEdge or edgeExists\n";
        return 1;
    }
    // Тестирование итератора соседей
    std::cout << "Neighbors of Vertex 2: ";
    MyGraph::NeighborIterator it(v2);
    while (it.hasNext()) {
        auto neighbor = it.next();
        std::cout << graph.getVertexData(neighbor) << " ";
    }
    std::cout << "\n";

    // Тестирование удаления ребра
    graph.removeEdge(e1);
    if (graph.edgeExists(v1, v2)) {
        std::cout << "Error in removeEdge\n";
        return 1;
    }

    // Тестирование удаления вершины
    graph.removeVertex(v3);
    if (graph.vertexCount() != 2) {
        std::cout << "Error in removeVertex\n";
        return 1;
    }

    return 0;
}