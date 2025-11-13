#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "queue.h"

using namespace std;

// Функция для поиска кратчайшего пути с помощью BFS
int bfs_shortest_path(int vertices, int start, int finish, const vector<vector<int>>& graph) {
    if (start == finish) return 0;
    
    Queue* queue = queue_create();
    vector<bool> visited(vertices + 1, false);
    vector<int> distance(vertices + 1, -1);
    
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
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << argv[1] << endl;
        return 1;
    }
    
    ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << argv[2] << endl;
        inputFile.close();
        return 1;
    }
    
    int vertices, start, finish;
    inputFile >> vertices >> start >> finish;
    
    // Создаем список смежности
    vector<vector<int>> graph(vertices + 1);
    
    string line;
    getline(inputFile, line); // Читаем оставшуюся часть первой строки
    
    while (getline(inputFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        int u, v;
        ss >> u >> v;
        
        graph[u].push_back(v);
        graph[v].push_back(u); // Граф неориентированный
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