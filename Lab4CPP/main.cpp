#include <iostream>
#include <climits>
#include "graph.h"
#include <cassert>

const int INF = INT_MAX;

template<typename Data>
void modifiedFloydWarshall(const Graph<Data>& graph, size_t vertex_amount) {
    Graph<Data> mutableGraph = graph;

    for (size_t k = 0; k < vertex_amount; ++k) {
        for (size_t i = 0; i < vertex_amount; ++i) {
            for (size_t j = 0; j < vertex_amount; ++j) {
                typename Graph<Data>::Edge* edgeIK = mutableGraph.getEdge(i, k);
                typename Graph<Data>::Edge* edgeKJ = mutableGraph.getEdge(k, j);

                if (edgeIK && edgeKJ) {
                    int weightIK = edgeIK->getEdgeData();
                    int weightKJ = edgeKJ->getEdgeData();

                    if (mutableGraph.getEdge(i, j) == nullptr ||
                        (weightIK != INF && weightKJ != INF &&
                        mutableGraph.getVertex(i).getVertexData() != INF &&
                        mutableGraph.getVertex(k).getVertexData() != INF &&
                        mutableGraph.getVertex(j).getVertexData() != INF &&
                        mutableGraph.getEdge(i, j)->getEdgeData() != INF &&
                        mutableGraph.getVertex(i).getVertexData() + weightIK + weightKJ >
                        mutableGraph.getVertex(j).getVertexData())) {
                        if (mutableGraph.getEdge(i, j) == nullptr) {
                            mutableGraph.addEdge(i, j, mutableGraph.getVertex(i).getVertexData() + weightIK + weightKJ);
                        } else {
                            mutableGraph.getEdge(i, j)->setEdgeData(mutableGraph.getVertex(i).getVertexData() + weightIK + weightKJ);
                        }
                    }
                }
            }
        }
    }

    std::cout << "Adjacency Matrix:\n";
    for (size_t i = 0; i < vertex_amount; ++i) {
        for (size_t j = 0; j < vertex_amount; ++j) {
            if (mutableGraph.getEdge(i, j)) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }

    size_t start_vertex = 0;
    size_t end_vertex = vertex_amount - 1; 
    if (mutableGraph.getEdge(start_vertex, end_vertex) != nullptr) {
        std::cout << "Longest path from vertex " << start_vertex << " to vertex " << end_vertex << " is "
                  << mutableGraph.getEdge(start_vertex, end_vertex)->getEdgeData() << "\n";
    } else {
        std::cout << "Longest path from vertex " << start_vertex << " to vertex " << end_vertex << " is NULL\n";
    }
}

int main() {
    size_t vertex_amount = 0; 
    int N = 0; 

    std::cout << "Input vertex_amount> ";
    std::cin >> vertex_amount;

    Graph<int> graph(vertex_amount);

    std::cout << "Input size read data> ";
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        size_t start_vertex_index, end_vertex_index;
        int edge_data;
        std::cout << "input " << i << " data (size_t start_vertex_index, size_t end_vertex_index, Data edge_data)> ";
        std::cin >> start_vertex_index >> end_vertex_index >> edge_data;
        graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
    }

    modifiedFloydWarshall(graph, vertex_amount);

    return 0;
}