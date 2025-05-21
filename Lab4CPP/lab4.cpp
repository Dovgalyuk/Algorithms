#include "graph.h"
#include <iostream>
#include <limits>

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

int main() {
    size_t vertexCount;
    std::cout << "Enter number of vertices: ";
    std::cin >> vertexCount;
    
    Graph<std::string, int> graph(vertexCount);
    
    for (size_t i = 0; i < vertexCount; ++i) {
        std::string label;
        std::cout << "Enter label for vertex " << i << ": ";
        std::cin >> label;
        graph.setVertexLabel(i, label);
    }
    
    size_t edgeCount;
    std::cout << "Enter number of edges: ";
    std::cin >> edgeCount;
    
    for (size_t i = 0; i < edgeCount; ++i) {
        size_t from, to;
        int weight;
        std::cout << "Enter edge " << i << " (from to weight): ";
        std::cin >> from >> to >> weight;
        graph.addEdge(from, to, weight);  
    }
    
    floydWarshall(graph);
    
    return 0;
}
