#include <iostream>
#include <fstream>
#include <climits>
#include "graph.h"

const int INF = INT_MAX;

template<typename Data>
void modifiedFloydWarshall(Graph<Data>& graph, size_t vertex_amount) {
    Graph<Data> mutableGraph = graph; // копия

    for (size_t k = 0; k < vertex_amount; ++k) {
        for (size_t i = 0; i < vertex_amount; ++i) {
            for (size_t j = 0; j < vertex_amount; ++j) {
                auto edgeIK = mutableGraph.getEdge(i, k);
                auto edgeKJ = mutableGraph.getEdge(k, j);

                if (edgeIK && edgeKJ) {
                    int weightIK = edgeIK->getEdgeData();
                    int weightKJ = edgeKJ->getEdgeData();

                    auto edgeIJ = mutableGraph.getEdge(i, j);
                    if (!edgeIJ || edgeIJ->getEdgeData() > weightIK + weightKJ) {
                        if (!edgeIJ)
                            mutableGraph.addEdge(i, j, weightIK + weightKJ);
                        else
                            edgeIJ->setEdgeData(weightIK + weightKJ);
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

    size_t start = 0, end = vertex_amount - 1;
    auto path = mutableGraph.getEdge(start, end);
    if (path)
        std::cout << "Shortest path from " << start << " to " << end << ": " << path->getEdgeData() << "\n";
    else
        std::cout << "No path from " << start << " to " << end << "\n";
}


int main(int argc, char* argv[]) {
    std::ifstream file("input.txt");
    std::istream* input = &std::cin;
    if (file)
        input = &file;
    else
        std::cout << "input.txt not found. Enter input manually.\n";

    size_t vertex_amount = 0;
    int edge_count = 0;

    std::cout << "Input vertex_amount> ";
    *input >> vertex_amount;
    Graph<int> graph(vertex_amount);

    std::cout << "Input number of edges> ";
    *input >> edge_count;

    for (int i = 0; i < edge_count; ++i) {
        size_t u, v;
        int weight;
        std::cout << "Edge " << i << " (start end weight): ";
        *input >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    modifiedFloydWarshall(graph, vertex_amount);
    return 0;
}
