#include "graph.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>

void floydWarshall(const Graph<std::string, int>& graph) {
    size_t n = graph.getVertexCount();
    
    Vector<Vector<int>> dist;
    dist.resize(n);
    for (size_t i = 0; i < n; ++i) {
        dist.set(i, Vector<int>());
        dist.get(i).resize(n);
        for (size_t j = 0; j < n; ++j) {
            if (i == j) {
                dist.get(i).set(j, 0);
            } else if (graph.hasEdge(i, j)) {
                dist.get(i).set(j, graph.getEdgeLabel(i, j));
            } else {
                dist.get(i).set(j, std::numeric_limits<int>::max());
            }
        }
    }
    
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (dist.get(i).get(k) != std::numeric_limits<int>::max() && 
                    dist.get(k).get(j) != std::numeric_limits<int>::max()) {
                    int newDist = dist.get(i).get(k) + dist.get(k).get(j);
                    if (newDist < dist.get(i).get(j)) {
                        dist.get(i).set(j, newDist);
                    }
                }
            }
        }
    }
    
    std::cout << "Shortest distances between all pairs of vertices:\n";
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            std::cout << graph.getVertexLabel(i) << " -> " << graph.getVertexLabel(j) << ": ";
            if (dist.get(i).get(j) == std::numeric_limits<int>::max()) {
                std::cout << "INF";
            } else {
                std::cout << dist.get(i).get(j);
            }
            std::cout << "\n";
        }
    }
}

void readGraphFromFile(const std::string& filename, Graph<std::string, int>& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    size_t vertexCount;
    file >> vertexCount;
    
    graph = Graph<std::string, int>(vertexCount);
    
    for (size_t i = 0; i < vertexCount; ++i) {
        std::string label;
        file >> label;
        graph.setVertexLabel(i, label);
    }
    
    size_t edgeCount;
    file >> edgeCount;
    
    for (size_t i = 0; i < edgeCount; ++i) {
        size_t from, to;
        int weight;
        file >> from >> to >> weight;
        graph.addEdge(from, to, weight);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    try {
        Graph<std::string, int> graph;
        readGraphFromFile(argv[1], graph);
        floydWarshall(graph);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
