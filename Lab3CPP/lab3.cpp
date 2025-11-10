#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "queue.h"
#include "list.h"
#include <vector>

typedef std::map<std::string, List*> Graph;

void add_road(Graph& graph, const std::string& a, const std::string& b) {
    if (graph.find(a) == graph.end()) graph[a] = list_create();
    if (graph.find(b) == graph.end()) graph[b] = list_create();

    list_insert(graph[a], b);
    list_insert(graph[b], a);
}

List* bfs(Graph& graph, const std::string& start, const std::string& end) {
    if (start == end) {
        List* path = list_create();
        list_insert(path, start);
        return path;
    }
    
    std::map<std::string, std::string> parent;
    std::map<std::string, bool> visited;

    Queue* q = queue_create();
    queue_insert(q, start);
    visited[start] = true;
    parent[start] = "";

    bool found = false;

    while (!queue_empty(q)) {
        std::string city = queue_get(q);
        queue_remove(q);
        
        if (city == end) {
            found = true;
            break;
        }

        auto it = graph.find(city);
        if (it == graph.end()) continue;

        ListItem* current = list_first(it->second);
        if (!current) continue;

        do {
            std::string neighbor = list_item_data(current);
            
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = city;
                queue_insert(q, neighbor);
            }
            
            current = list_item_next(current);
        } while (current && current != list_first(it->second));
    }

    queue_delete(q);

    List* path = list_create();
    if (!found) return path;

    std::string current_city = end;
    while (current_city != "") {
        list_insert(path, current_city);
        current_city = parent[current_city];
    }

    return path;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    std::ifstream ifile(argv[1]);
    std::ofstream ofile(argv[2]);

    if (!ifile.is_open() || !ofile.is_open()) return 1;

    std::vector<std::pair<std::string, std::string>> roads;
    std::string a, b;

    while (ifile >> a >> b) {
        roads.emplace_back(a, b);
    }

    if (roads.empty()) {
        ofile << "No data\n";
        std::cout << "No data\n";
        return 1;
    }

    std::string start = roads.back().first;
    std::string end = roads.back().second;
    roads.pop_back();

    Graph graph;
    for (auto& road : roads) {
        add_road(graph, road.first, road.second);
    }

    List* path = bfs(graph, start, end);

    if (!list_first(path)) {
        ofile << "Not found\n";
        std::cout << "Not found\n";
    } else {
        ListItem* current = list_first(path);
        bool first = true;
        
        do {
            if (!first) {
                ofile << " ";
                std::cout << " ";
            }
            ofile << list_item_data(current);
            std::cout << list_item_data(current);
            first = false;
            
            current = list_item_next(current);
        } while (current && current != list_first(path));
        
        ofile << "\n";
        std::cout << "\n";
    }

    for (auto& entry : graph) {
        list_delete(entry.second);
    }
    list_delete(path);

    return 0;
}