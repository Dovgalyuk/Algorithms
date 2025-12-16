#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "queue.h"

using namespace std;

// Псевдонимы типов для упрощения кода
using AdjacencyList = unordered_map<string, vector<string>>;
using CityList = vector<string>;
using Path = vector<string>;
using ParentMap = unordered_map<string, string>;
using CityIndexMap = unordered_map<string, int>;

// Структура для хранения графа
struct Graph {
    AdjacencyList adj;

    void addEdge(const string& u, const string& v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    CityList getNeighbors(const string& city) {
        if (adj.contains(city)) {
            return adj[city];
        }
        return {};
    }
};

// BFS для поиска кратчайшего пути
Path bfsShortestPath(Graph& graph, const string& start, const string& end) {
    if (start == end) return {start};

    ParentMap parent;
    Queue* queue = queue_create();
    
    parent[start] = "";
    CityList cities;
    CityIndexMap cityIndex;
    
    cityIndex[start] = cities.size();
    cities.push_back(start);
    queue_insert(queue, cityIndex[start]);

    bool found = false;

    while (!queue_empty(queue)) {
        int currentIdx = queue_get(queue);
        queue_remove(queue);
        string current = cities[currentIdx];

        CityList neighbors = graph.getNeighbors(current);
        for (const string& neighbor : neighbors) {
            if (!parent.contains(neighbor)) {
                parent[neighbor] = current;
                
                if (neighbor == end) {
                    found = true;
                    break;
                }
                
                if (!cityIndex.contains(neighbor)) {
                    cityIndex[neighbor] = cities.size();
                    cities.push_back(neighbor);
                }
                
                queue_insert(queue, cityIndex[neighbor]);
            }
        }
        if (found) break;
    }

    queue_delete(queue);

    if (found) {
        Path path;
        string node = end;
        while (node != start) {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }

    return {};
}

int main(int argc, char* argv[]) {
    string inputFile = (argc >= 2) ? argv[1] : "input.txt";
    
    ifstream input(inputFile);
    if (!input.is_open()) {
        cerr << "Error: Cannot open input file: " << inputFile << endl;
        return 1;
    }

    Graph graph;
    CityList lines;
    string line;

    while (getline(input, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    input.close();

    if (lines.empty()) {
        cerr << "Error: Input file is empty" << endl;
        return 1;
    }

    string lastLine = lines.back();
    lines.pop_back();

    size_t spacePos = lastLine.find(' ');
    if (spacePos == string::npos) {
        cerr << "Error: Invalid format in last line: " << lastLine << endl;
        return 1;
    }

    string start = lastLine.substr(0, spacePos);
    string end = lastLine.substr(spacePos + 1);

    for (const string& roadLine : lines) {
        size_t pos = roadLine.find(' ');
        if (pos != string::npos) {
            string city1 = roadLine.substr(0, pos);
            string city2 = roadLine.substr(pos + 1);
            if (!city1.empty() && !city2.empty()) {
                graph.addEdge(city1, city2);
            }
        }
    }

    Path path = bfsShortestPath(graph, start, end);

    if (!path.empty()) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " ";
        }
        cout << endl;
    } else {
        cout << "No path found" << endl;
    }

    return 0;
}
