#include <iostream>
#include <fstream>
#include <algorithm>
#include "graph.h"
#include "dsu.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: specify the input data file." << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error: cannot open file " << argv[1] << std::endl;
        return 1;
    }

    size_t n, m;
    infile >> n >> m;

    Graph<std::string, int> graph(n);
    for (size_t i = 0; i < n; ++i) {
        std::string name;
        infile >> name;
        graph.setVertexLabel(i, name);
    }

    for (size_t i = 0; i < m; ++i) {
        size_t from, to;
        int weight;
        infile >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }

    auto edges = graph.getEdges();
    std::sort(edges.begin(), edges.end(), [](const Graph<std::string, int>::Edge& a, const Graph<std::string, int>::Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(graph.getVertexCount());
    int totalWeight = 0;

    std::cout << "Minimum Spanning Tree:\n";
    for (const auto& e : edges) {
        if (dsu.find(e.from) != dsu.find(e.to)) {
            dsu.unite(e.from, e.to);
            totalWeight += e.weight;
            std::cout << graph.getVertexLabel(e.from) << " -- "
                      << graph.getVertexLabel(e.to) << " [" << e.weight << "]\n";
        }
    }

    std::cout << "Total weight: " << totalWeight << "\n";
    return 0;
}
