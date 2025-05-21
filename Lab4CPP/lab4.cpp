#include "graph.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <string>

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

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
            return 1;
        }

        std::ifstream infile(argv[1]);
        if (!infile) {
            std::cerr << "Error: cannot open file " << argv[1] << std::endl;
            return 1;
        }

        size_t vertexCount, edgeCount;
        if (!(infile >> vertexCount >> edgeCount)) {
            std::cerr << "Error reading vertex and edge counts" << std::endl;
            return 1;
        }

        Graph<std::string, int> graph;
        
        for (size_t i = 0; i < vertexCount; ++i) {
            std::string label;
            if (!(infile >> label)) {
                std::cerr << "Error reading vertex label " << i << std::endl;
                return 1;
            }
            graph.addVertex(label);
        }
        
        for (size_t i = 0; i < edgeCount; ++i) {
            size_t from, to;
            int weight;
            if (!(infile >> from >> to >> weight)) {
                std::cerr << "Error reading edge " << i << std::endl;
                return 1;
            }
            if (from >= vertexCount || to >= vertexCount) {
                std::cerr << "Invalid vertex index in edge " << i 
                          << ": " << from << " or " << to 
                          << " (vertex count = " << vertexCount << ")" << std::endl;
                return 1;
            }
            graph.addEdge(from, to, weight);
        }

        infile.close();

        floydWarshall(graph);
        
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
