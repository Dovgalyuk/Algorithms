#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <stdexcept>
#include "graph.h"
#include "vector.h"

Graph<std::string, int> read_graph_from_file(const std::string& filename) {
    std::ifstream file(filename);

    int n;
    file >> n;
    
    Graph<std::string, int> graph;
    
    for(int i = 0; i < n; i++) {
        std::string vertex_name;
        file >> vertex_name;
        graph.add_vertex(vertex_name);
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int weight;
            file >> weight;
            if(weight != 0) { 
                graph.set_edge(i, j, weight);
            }
        }
    }
    file.close();
    return graph;
}

void floyd_algorithm(Graph<std::string, int>& graph) {
    size_t n = graph.vertex_count();
    
    Vector<Vector<int>> dist;
    dist.resize(n);
    for(size_t i = 0; i < n; i++) {
        dist[i].resize(n);
        for(size_t j = 0; j < n; j++)
            dist[i][j] = INT_MAX;
    }

    Vector<Vector<int>> next;
    next.resize(n);
    for(size_t i = 0; i < n; i++) {
        next[i].resize(n);
        for(size_t j = 0; j < n; j++)
            next[i][j] = -1;
    }

    
    for(size_t i = 0; i < n; i++) {
        dist[i][i] = 0;
        next[i][i] = i;
        
        for(size_t j = 0; j < n; j++) {
            if(i != j && graph.has_edge(i, j)) {
                try{
                    dist[i][j] = graph.get_edge(i, j);
                    next[i][j] = j;
                }
                catch(const std::out_of_range& e)
                {
                    std::cout << "Edge error: " << e.what() << "\n";
                }
            }
        }
    }
    
    for(size_t k = 0; k < n; k++) {
        for(size_t i = 0; i < n; i++) {
            for(size_t j = 0; j < n; j++) {
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && 
                   dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    std::cout << "\t";
    for(size_t i = 0; i < n; i++) {
        std::cout << graph.get_vertex(i) << "\t";
    }
    std::cout << "\n";
    
    for(size_t i = 0; i < n; i++) {
        std::cout << graph.get_vertex(i) << "\t";
        for(size_t j = 0; j < n; j++) {
            if(dist[i][j] == INT_MAX) {
                std::cout << "INF\t";
            } else {
                std::cout << dist[i][j] << "\t";
            }
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    try {
        if(argc < 2) {
            return 1;
        }
        Graph<std::string, int> graph = read_graph_from_file(argv[1]);
        floyd_algorithm(graph);
        
    } catch(const std::exception& e) {
        std::cout << e.what() << "\n";
        return 1;
    }
    
    return 0;
}