#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "queue.h"

typedef std::vector<std::vector<int>> Graph;

int bfs_shortest_path(int vertices, int start, int finish, const Graph& graph) {
    if (start == finish) return 0;
    
    Queue* queue = queue_create();
    std::vector<bool> visited(vertices + 1, false);
    std::vector<int> distance(vertices + 1, -1);
    
    queue_insert(queue, start);
    visited[start] = true;
    distance[start] = 0;
    
    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);
        
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                queue_insert(queue, neighbor);
                
                if (neighbor == finish) {
                    queue_delete(queue);
                    return distance[neighbor];
                }
            }
        }
    }
    
    queue_delete(queue);
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file: " << argv[1] << std::endl;
        return 1;
    }
    
    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file: " << argv[2] << std::endl;
        inputFile.close();
        return 1;
    }
    
    int vertices, start, finish;
    inputFile >> vertices >> start >> finish;
    
    // Создаем список смежности
    Graph graph(vertices + 1);
    
    std::string line;
    std::getline(inputFile, line);
    
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        int u, v;
        ss >> u >> v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    inputFile.close();
    
    int result = bfs_shortest_path(vertices, start, finish, graph);
    
    if (result != -1) {
        outputFile << result;
    } else {
        outputFile << "IMPOSSIBLE";
    }
    
    outputFile.close();
    return 0;
}