#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>
#include <algorithm>  

#include "queue.h"
#include "vector.h"

struct Graph {
    std::vector<std::vector<int>> adjacency_list;
    size_t vertices_count;
};

Graph create_graph(size_t vertices_count) {
    Graph graph;
    graph.vertices_count = vertices_count;
    graph.adjacency_list.resize(vertices_count + 1); 
    return graph;
}

void add_edge(Graph& graph, int u, int v) {
    graph.adjacency_list[u].push_back(v);
    graph.adjacency_list[v].push_back(u); 
}

std::vector<int> find_shortest_path(const Graph& graph, int start, int finish) {
    size_t n = graph.vertices_count;
    
    std::vector<bool> visited(n + 1, false);
    std::vector<int> parent(n + 1, -1);
    
    Queue* queue = queue_create();
    
    visited[start] = true;
    queue_insert(queue, start);
    
    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);
        
        if (current == finish) {
            break;
        }
        
        for (int neighbor : graph.adjacency_list[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                queue_insert(queue, neighbor);
            }
        }
    }
    
    queue_delete(queue);
    
    std::vector<int> path;
    
    if (parent[finish] != -1 || start == finish) {
        int current = finish;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        std::reverse(path.begin(), path.end());
    }
    
    return path;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }
    
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    
    if (!input.is_open()) {
        std::cerr << "Cannot open input file: " << argv[1] << "\n";
        return 1;
    }
    
    if (!output.is_open()) {
        std::cerr << "Cannot open output file: " << argv[2] << "\n";
        return 1;
    }
    
    int vertices_count, start, finish;
    input >> vertices_count >> start >> finish;
    
    Graph graph = create_graph(vertices_count);
    
    int u, v;
    while (input >> u >> v) {
        add_edge(graph, u, v);
    }
    
    std::vector<int> path = find_shortest_path(graph, start, finish);
    
    if (path.empty()) {
        output << "IMPOSSIBLE\n";
    } else {
        for (size_t i = 0; i < path.size(); ++i) {
            output << path[i];
            if (i < path.size() - 1) {
                output << " ";
            }
        }
        output << "\n";
    }
    
    input.close();
    output.close();
    
    return 0;
}