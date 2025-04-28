#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Graph.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: specify the input data file." << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    size_t vertexCount, edgeCount;
    infile >> vertexCount >> edgeCount;

     Graph<std::string, int> graph(vertexCount);

    for (size_t i = 0; i < edgeCount; ++i) {
        size_t from, to;
        int weight;
        infile >> from >> to >> weight;
        graph.add_Edge(from, to, weight);
    }

    std::vector<EdgeInfo<int>> edges = graph.get_edges();
    std::sort(edges.begin(), edges.end(), [](const EdgeInfo<int>& a, const EdgeInfo<int>& b) {
        return a.weight < b.weight;
    });

    DSU dsu(vertexCount);

    int totalWeight = 0;
    std::vector<EdgeInfo<int>> mst;

    for (const auto& edge : edges) {
        if (dsu.find(edge.vertex1) != dsu.find(edge.vertex2)) {
            dsu.union_sets(edge.vertex1, edge.vertex2);
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
    }

    std::cout << "Minimum Spanning Tree edges:\n";
    for (const auto& edge : mst) {
        std::cout << edge.vertex1 << " -- " << edge.vertex2 << " [weight=" << edge.weight << "]\n";
    }
    std::cout << "Total weight: " << totalWeight << std::endl;

    return 0;
}
