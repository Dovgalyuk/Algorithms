#include "graph.h"
#include "vector.h"
#include <iostream>
#include <cassert>

int main() {
    Graph<std::string, double> g(3);
    g.setVertexLabel(0, "A");
    g.setVertexLabel(1, "B");
    g.setVertexLabel(2, "C");

    g.addEdge(0, 1, 1.0);
    g.addEdge(1, 2, 2.0);

    if (!g.hasEdge(0, 1)) {
        std::cerr << "Edge 0->1 should exist" << std::endl;
        return 1;
    }
    if (g.hasEdge(1, 0)) {
        std::cerr << "Edge 1->0 should not exist" << std::endl;
        return 1;
    }
    if (g.getEdgeLabel(0, 1).value() != 1.0) {
        std::cerr << "Wrong edge label" << std::endl;
        return 1;
    }

    if (g.getVertexLabel(0) != "A") {
        std::cerr << "Wrong vertex label" << std::endl;
        return 1;
    }

    auto labels = g.getAllVertexLabels();
    if (labels.size() != 3 || labels[0] != "A") {
        std::cerr << "Wrong vertex labels" << std::endl;
        return 1;
    }

    g.addVertex("D");
    if (g.numVertices() != 4) {
        std::cerr << "Wrong number of vertices" << std::endl;
        return 1;
    }
    if (g.getVertexLabel(3) != "D") {
        std::cerr << "Wrong vertex label for new vertex" << std::endl;
        return 1;
    }

    g.removeEdge(0, 1);
    if (g.hasEdge(0, 1)) {
        std::cerr << "Edge should be removed" << std::endl;
        return 1;
    }

    g.addEdge(0, 2, 3.0);
    g.addEdge(0, 3, 4.0);
    g.addEdge(0, 1, 1.0);

    size_t neighbor_count = 0;
    for (auto it = g.beginNeighbors(0); it != g.endNeighbors(0); ++it) {
        neighbor_count++;
    }

    if (neighbor_count != 3) {
        std::cerr << "Iterator test failed: expected 3 neighbors, got "
            << neighbor_count << std::endl;
        return 1;
    }

    g.removeVertex(1);
    if (g.numVertices() != 3) {
        std::cerr << "Wrong number of vertices after removal" << std::endl;
        return 1;
    }

    std::cout << "All graph tests passed!" << std::endl;
    return 0;
}