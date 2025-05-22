#include "graph.h"
#include "vector.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>

void floydWarshall(const Graph<std::string, int>& graph) {
    size_t n = graph.getVertexCount();
    
    Vector<Vector<int>> dist;
    Vector<Vector<int>> next;
    dist.resize(n);
    next.resize(n);
        
    for (size_t i = 0; i < n; ++i) {
        dist[i].resize(n);  
        next[i].resize(n);
        
        for (size_t j = 0; j < n; ++j) {
            dist[i][j] = std::numeric_limits<int>::max();
            next[i][j] = -1; 
        }
        
        dist[i][i] = 0;
        next[i][i] = i;

        auto it = graph.getIterator(i);
        while (it.hasNext()) {
            size_t j = it.next();
            dist[i][j] = graph.getEdgeLabel(i, j);
            next[i][j] = j;
        }
    }
    
    // Алгоритм Флойда-Уоршелла
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (dist[i][k] != std::numeric_limits<int>::max() && 
                    dist[k][j] != std::numeric_limits<int>::max() &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];}
            }
        }
    }
    
    auto getPath = [&](size_t from, size_t to) -> Vector<size_t> {
        Vector<size_t> path;
        if (next[from][to] == -1) return path;  
        
        path.push_back(from);
        while (from != to) {
            from = next[from][to];
            path.push_back(from);
        }
        return path;
    };
    
    std::cout << "Shortest paths between all pairs of vertices:\n";
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i == j) continue; 
            
            std::cout << graph.getVertexLabel(i) << " -> " << graph.getVertexLabel(j) << ": ";
            
            if (dist[i][j] == std::numeric_limits<int>::max()) {
                std::cout << "No path";
            } else {
                
                auto path = getPath(i, j);
                for (size_t k = 0; k < path.size(); ++k) {
                    if (k != 0) std::cout << " -> ";
                    std::cout << graph.getVertexLabel(path[k]);
                }
                std::cout << " (distance: " << dist[i][j] << ")";
            }
            std::cout << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    const char* filename = "input.txt";
    
    if (argc > 1) {
        filename = argv[1];
    }
    
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return 1;
    }

    size_t vertexCount;
    inputFile >> vertexCount;
    inputFile.ignore();

    Graph<std::string, int> graph(vertexCount);
    
    for (size_t i = 0; i < vertexCount; ++i) {
        std::string label;
        std::getline(inputFile, label);
        graph.setVertexLabel(i, label);
    }
    
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        size_t from, to;
        int weight;
        
        if (!(iss >> from >> to >> weight)) {
            std::cerr << "Error: invalid edge format in line: " << line << std::endl;
            continue;
        }
        
        if (from >= vertexCount || to >= vertexCount) {
            std::cerr << "Error: vertex index out of range in line: " << line << std::endl;
            continue;
        }
        
        graph.addEdge(from, to, weight);
    }
    
    floydWarshall(graph);
    
    return 0;
}
