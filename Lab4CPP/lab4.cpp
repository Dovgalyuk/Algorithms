#include <iostream>
#include <fstream>
#include <algorithm>
#include "Graph.h"
#include "DSU.cpp"

struct EdgeInfo {
    int u, v;
    int weight;

    bool operator<(const EdgeInfo& other) const {
        return weight < other.weight;
    }
};

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

    Graph<std::string, int> graph;
    int vertexCount, edgeCount;
    infile >> vertexCount >> edgeCount;

    for (int i = 0; i < vertexCount; ++i) {
        std::string label;
        infile >> label;
        graph.add_Vertex(label);
    }

    for (int i = 0; i < edgeCount; ++i) {
        int from, to, weight;
        infile >> from >> to >> weight;
        graph.add_Edge(from, to, weight);
        graph.add_Edge(to, from, weight);
    }

    Vector<EdgeInfo> edges;

    for (int u = 0; u < vertexCount; ++u) {
        auto it = graph.get_Iterator(u);
        while (it.hasNext()) {
            int v = it.next();
            int weight = graph.get_Edge_Mark(u, v);
            if (u < v) {
                edges.push_back({u, v, weight});
            }
        }
    }

    std::vector<EdgeInfo> edges_std;
    for (size_t i = 0; i < edges.size(); ++i) {
        edges_std.push_back(edges.get(i));
    }
    std::sort(edges_std.begin(), edges_std.end());

    edges.clear();
    for (const auto& e : edges_std) {
        edges.push_back(e);
    }

    DSU dsu(vertexCount);

    int totalWeight = 0;
    Vector<EdgeInfo> mst;

    for (size_t i = 0; i < edges.size(); ++i) {
        const auto& edge = edges.get(i);
        if (dsu.find_set(edge.u) != dsu.find_set(edge.v)) {
            dsu.union_sets(edge.u, edge.v);
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
    }

    std::cout << "Minimum Spanning Tree edges:\n";
    for (size_t i = 0; i < mst.size(); ++i) {
        const auto& edge = mst.get(i);
        std::cout << edge.u << " -- " << edge.v << " [weight=" << edge.weight << "]\n";
    }
    std::cout << "Total weight: " << totalWeight << std::endl;

    return 0;
}
