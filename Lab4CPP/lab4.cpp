#include <iostream>
#include <fstream>
#include <limits>
#include "graph.h"
#include "vector.h"

void printShortestPaths(const Graph<int, std::string>& graph, const Vector<Vector<int>>& dist) {
    size_t n = graph.vertexCount();
    std::cout << "\nShortest paths between all vertices:\n";
    std::cout << "\t";
    

    for (size_t j = 0; j < n; ++j) {
        std::cout << graph.getVertexData(j) << "\t";
    }
    std::cout << "\n";
    
    for (size_t i = 0; i < n; ++i) {
        std::cout << graph.getVertexData(i) << ":\t";
        for (size_t j = 0; j < n; ++j) {
            if (dist.get(i).get(j) == std::numeric_limits<int>::max()) {
                std::cout << "INF\t";
            } else {
                std::cout << dist.get(i).get(j) << "\t";
            }
        }
        std::cout << "\n";
    }
}

void floydWarshall(const Graph<int, std::string>& graph) {
    size_t n = graph.vertexCount();
    Vector<Vector<int>> dist;
    
    dist.resize(n);
    for (size_t i = 0; i < n; ++i) {
        dist.set(i, Vector<int>());
        dist.get(i).resize(n);
        
        for (size_t j = 0; j < n; ++j) {
            if (i == j) {
                dist.get(i).set(j, 0);
            } else if (graph.hasEdge(i, j)) {
                dist.get(i).set(j, graph.getEdgeData(i, j));
            } else {
                dist.get(i).set(j, std::numeric_limits<int>::max());
            }
        }
    }
    
    // Алгоритм Флойда-Уоршелла
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
    
    printShortestPaths(graph, dist);
}

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

    Graph<int, std::string> graph(n);
    
    for (size_t i = 0; i < n; ++i) {
        std::string name;
        infile >> name;
        graph.setVertexData(i, name);
    }

    for (size_t i = 0; i < m; ++i) {
        size_t from, to;
        int weight;
        infile >> from >> to >> weight;
        
        if (from >= n || to >= n) {
            std::cerr << "Error: invalid vertex index in edge " 
                      << from << " -> " << to << std::endl;
            return 1;
        }
        
        graph.addEdge(from, to);
        graph.setEdgeData(from, to, weight);
    }

    std::cout << "Graph loaded successfully with " << n << " vertices and " << m << " edges\n";
    
    floydWarshall(graph);

    return 0;
}
