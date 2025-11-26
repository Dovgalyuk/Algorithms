#include <iostream>
#include "dirgraph.h"

struct VertexData {
    int id = 0;
    VertexData(int i = 0) : id(i) {}
    bool operator==(const VertexData& other) const { return id == other.id; }
};
struct EdgeData {
    int weight = 0;
    EdgeData(int w = 0) : weight(w) {}
    bool operator==(const EdgeData& other) const { return weight == other.weight; }
};

int main() {
    DirGraph<VertexData, EdgeData> graph;

    auto v0 = graph.addVertex(VertexData(0));
    auto v1 = graph.addVertex(VertexData(10));
    auto v2 = graph.addVertex(VertexData(20));

    std::cout << "Created vertices: " << v0 << ", " << v1 << ", " << v2 << std::endl;

    if (!(graph.getVertexMark(v0) == VertexData(0))) return 1;
    if (!graph.addEdge(v0, v1, EdgeData(5))) return 1;
    if (!graph.edgeExists(v0, v1)) return 1;
    if (!(graph.getEdgeMark(v0, v1) == EdgeData(5))) return 1;

    graph.removeEdge(v0, v1);
    if (graph.edgeExists(v0, v1)) return 1;

    graph.removeVertex(v2);
    if (graph.getVertexCount() != 2) return 1;

    graph.addEdge(v0, v1, EdgeData(10));
    if (!graph.edgeExists(v0, v1)) return 1;

    std::cout << "Neighbors of vertex " << v0 << ": ";
    for (auto it = graph.neighborsBegin(v0); it != graph.neighborsEnd(v0); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "All tests passed";
    return 0;
}