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

    vector<string> getNeighbors(const string& city) {
        auto it = adj.find(city);
        if (it != adj.end()) {
            return it->second;
        }
        return {};
    }
};

// BFS для поиска кратчайшего пути
vector<string> bfsShortestPath(Graph& graph, const string& start, const string& end) {
    if (start == end) {
        return { start };
    }

    // Словари для BFS
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;

    // Очередь для BFS
    Queue* queue = queue_create();

    // Инициализация BFS
    visited[start] = true;

    vector<string> cities;
    unordered_map<string, int> cityIndex;

    // Добавляем стартовый город
    cityIndex[start] = cities.size();
    cities.push_back(start);
    queue_insert(queue, cityIndex[start]);

    bool found = false;

    while (!queue_empty(queue)) {
        int currentIdx = queue_get(queue);
        queue_remove(queue);

        string current = cities[currentIdx];

        // Получаем соседей
        vector<string> neighbors = graph.getNeighbors(current);
        for (const string& neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;

                // Если нашли конечный город
                if (neighbor == end) {
                    found = true;
                    break;
                }

                // Добавляем город в список, если его еще нет
                if (cityIndex.find(neighbor) == cityIndex.end()) {
                    cityIndex[neighbor] = cities.size();
                    cities.push_back(neighbor);
                }

                queue_insert(queue, cityIndex[neighbor]);
            }
        }

        if (found) {
            break;
        }
    }

    queue_delete(queue);

    // Восстанавливаем путь, если нашли
    if (found) {
        vector<string> path;
        string node = end;

        while (node != start) {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return path;
    }

    return {}; // путь не найден
}

int main(int argc, char* argv[]) {
    string inputFile = "input.txt";

    if (argc >= 2) {
        inputFile = argv[1];
    }

    ifstream input(inputFile);
    if (!input.is_open()) {
        cerr << "Error: Cannot open input file: " << inputFile << endl;
        return 1;
    }

    Graph graph;
    vector<string> lines;
    string line;

    while (getline(input, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
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
        cerr << "Error: Invalid format in last line (start and end cities): " << lastLine << endl;
        cerr << "Expected format: 'StartCity EndCity'" << endl;
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

    // Поиск кратчайшего пути
    vector<string> path = bfsShortestPath(graph, start, end);

    // Вывод результата
    if (!path.empty()) {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    else {
        cout << "No path found" << endl;
    }

    return 0;
}
