#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "queue.h"

using namespace std;

// Структура для хранения графа
struct Graph {
    unordered_map<string, vector<string>> adj;
    
    void addEdge(const string& u, const string& v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // дороги двунаправленные
    }
};

// BFS для поиска кратчайшего пути
vector<string> bfsShortestPath(Graph& graph, const string& start, const string& end) {
    if (start == end) {
        return {start};
    }
    
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;
    Queue* queue = queue_create();
    
    // Инициализация BFS
    visited[start] = true;
    queue_insert(queue, (Data)&start);
    
    while (!queue_empty(queue)) {
        string current = *(string*)queue_get(queue);
        queue_remove(queue);
        
        if (!graph.adj.count(current)) continue;
        
        for (const string& neighbor : graph.adj[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                
                if (neighbor == end) {
                    // Нашли путь, восстанавливаем его
                    vector<string> path;
                    string node = end;
                    
                    while (node != start) {
                        path.push_back(node);
                        node = parent[node];
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end());
                    
                    queue_delete(queue);
                    return path;
                }
                
                queue_insert(queue, (Data)&neighbor);
            }
        }
    }
    
    queue_delete(queue);
    return {}; // путь не найден
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    
    ifstream input(argv[1]);
    ofstream output(argv[2]);
    
    if (!input.is_open()) {
        cerr << "Cannot open input file: " << argv[1] << endl;
        return 1;
    }
    
    if (!output.is_open()) {
        cerr << "Cannot open output file: " << argv[2] << endl;
        return 1;
    }
    
    Graph graph;
    vector<pair<string, string>> roads;
    string city1, city2;
    
    // Чтение дорог
    while (input >> city1 >> city2) {
        roads.push_back({city1, city2});
        graph.addEdge(city1, city2);
    }
    
    if (roads.size() < 2) {
        cerr << "Not enough data in input file" << endl;
        return 1;
    }
    
    // Последние два города - начальный и конечный
    string start = roads.back().first;
    string end = roads.back().second;
    
    // Удаляем последнюю пару из списка дорог
    roads.pop_back();
    
    // Поиск кратчайшего пути
    vector<string> path = bfsShortestPath(graph, start, end);
    
    // Вывод результата
    if (!path.empty()) {
        for (size_t i = 0; i < path.size(); ++i) {
            output << path[i];
            if (i < path.size() - 1) {
                output << " ";
            }
        }
        output << endl;
    } else {
        output << "No path found" << endl;
    }
    
    return 0;
}
