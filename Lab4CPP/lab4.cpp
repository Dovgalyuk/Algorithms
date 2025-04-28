#include <iostream>
#include <fstream>
#include <algorithm>
#include "Graph.h"

struct EdgeInfo {
    size_t u, v;
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

    size_t vertexCount, edgeCount;
    infile >> vertexCount >> edgeCount;

    Graph graph(vertexCount);

    for (size_t i = 0; i < edgeCount; ++i) {
        size_t from, to;
        int weight;
        infile >> from >> to >> weight;
        graph.add_edge(from, to, weight);
    }

    Vector<EdgeInfo> edges;

    for (size_t u = 0; u < vertexCount; ++u) {
        auto it = graph.iterator(u);
        while (it.has_next()) {
            size_t v = it.next();
            int weight = 0;
            for (size_t i = 0; i < graph.get_edges().size(); ++i) {
                if (graph.get_edges().get(i).from == u && graph.get_edges().get(i).to == v) {
                    weight = graph.get_edges().get(i).weight;
                    break;
                }
            }
            if (u < v) {
                edges.push_back({u, v, weight});
            }
        }
    }

    std::sort(edges.get(0), edges.get(edges.size() - 1));

    DSU dsu(vertexCount);

    int totalWeight = 0;
    Vector<EdgeInfo> mst;

    for (size_t i = 0; i < edges.size(); ++i) {
        const auto& edge = edges.get(i);
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
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
