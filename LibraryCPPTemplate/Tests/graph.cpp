#include <iostream>
#include "graph.h"

int main() {
    Graph<int, int> graph(8, 8);

    graph.setVertexData(0, 0, 42);
    if (graph.getVertexData(0, 0) != 42) {
        std::cout << "Fail: get/set vertex data\n"; return 1;
    }

    Vector<int> all_vertices = graph.getVertices();
    if (all_vertices.size() != 64 || all_vertices.get(0) != 42) {
        std::cout << "Fail: getVertices\n"; return 1;
    }

    if (!graph.hasEdge(0, 0, 0, 1)) {
        std::cout << "Fail: hasEdge should be true\n"; return 1;
    }

    graph.removeEdge(0, 0, 0, 1);
    if (graph.hasEdge(0, 0, 0, 1)) {
        std::cout << "Fail: removeEdge failed\n"; return 1;
    }

    int count_00 = 0;
    for (auto it = graph.begin(0, 0); it != graph.end(0, 0); ++it) {
        count_00++;
    }
    if (count_00 != 1) {
        std::cout << "Fail: Iterator should skip removed edge\n"; return 1;
    }

    graph.addEdge(0, 0, 0, 1);
    if (!graph.hasEdge(0, 0, 0, 1)) {
        std::cout << "Fail: addEdge failed\n"; return 1;
    }

    graph.setEdgeData(0, 0, 0, 1, 999);
    if (graph.getEdgeData(0, 0, 0, 1) != 999) {
        std::cout << "Fail: edge data get/set\n"; return 1;
    }

    int count_center = 0;
    for (auto it = graph.begin(4, 4); it != graph.end(4, 4); ++it) {
        count_center++;
    }
    if (count_center != 6) {
        std::cout << "Fail: center should have 6 neighbors\n"; return 1;
    }

    std::cout << "Graph test passed!\n";
    return 0;
}