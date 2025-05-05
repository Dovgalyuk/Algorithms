#include <iostream>
#include <fstream>
#include <climits>
#include "graph.h"
#include <cassert>

const int INF = INT_MAX;

template<typename Data>
void modifiedFloydWarshall(Graph<Data>& graph, size_t vertex_amount) {
    Graph<Data> mutableGraph = graph;

    for (size_t k = 0; k < vertex_amount; ++k) {
        for (size_t i = 0; i < vertex_amount; ++i) {
            for (size_t j = 0; j < vertex_amount; ++j) {
                auto edgeIK = mutableGraph.getEdge(i, k);
                auto edgeKJ = mutableGraph.getEdge(k, j);

                if (edgeIK && edgeKJ) {
                    int weightIK = edgeIK->getEdgeData();
                    int weightKJ = edgeKJ->getEdgeData();

                    if (mutableGraph.getEdge(i, j) == nullptr ||
                        (weightIK != INF && weightKJ != INF &&
                         mutableGraph.getEdge(i, j)->getEdgeData() > weightIK + weightKJ)) {
                        if (mutableGraph.getEdge(i, j) == nullptr) {
                            mutableGraph.addEdge(i, j, weightIK + weightKJ);
                        } else {
                            mutableGraph.getEdge(i, j)->setEdgeData(weightIK + weightKJ);
                        }
                    }
                }
            }
        }
    }

    std::cout << "Adjacency Matrix:\n";
    for (size_t i = 0; i < vertex_amount; ++i) {
        for (size_t j = 0; j < vertex_amount; ++j) {
            std::cout << (mutableGraph.getEdge(i, j) ? "1 " : "0 ");
        }
        std::cout << "\n";
    }

    size_t start_vertex = 0;
    size_t end_vertex = vertex_amount - 1;
    if (mutableGraph.getEdge(start_vertex, end_vertex)) {
        std::cout << "Shortest path from vertex " << start_vertex << " to vertex " << end_vertex
                  << " is " << mutableGraph.getEdge(start_vertex, end_vertex)->getEdgeData() << "\n";
    } else {
        std::cout << "No path from vertex " << start_vertex << " to vertex " << end_vertex << "\n";
    }
}

int main(int argc, char* argv[]) {
    size_t vertex_amount = 0;
    int N = 0;
    std::ifstream infile;
    std::istream* in = &std::cin;

    if (argc > 1) {
        infile.open(argv[1]);
        if (infile.is_open()) {
            in = &infile;
            std::cout << "Reading input from file: " << argv[1] << "\n";
        } else {
            std::cerr << "Failed to open file: " << argv[1] << ". Switching to manual input.\n";
        }
    } else {
        std::cout << "No input file provided. Using manual input.\n";
    }

    std::cout << "Input vertex_amount> ";
    *in >> vertex_amount;

    if (vertex_amount == 0) {
        std::cerr << "Invalid vertex amount.\n";
        return 1;
    }

    Graph<int> graph(vertex_amount);

    std::cout << "Input number of edges> ";
    *in >> N;

    for (int i = 0; i < N; ++i) {
        size_t start_vertex_index, end_vertex_index;
        int edge_data;
        std::cout << "Input " << i << " data (start_vertex end_vertex weight)> ";
        *in >> start_vertex_index >> end_vertex_index >> edge_data;

        if (start_vertex_index >= vertex_amount || end_vertex_index >= vertex_amount) {
            std::cerr << "Invalid edge index: " << start_vertex_index << " -> " << end_vertex_index << "\n";
            return 1;
        }

        graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
    }

    modifiedFloydWarshall(graph, vertex_amount);
    return 0;
}
