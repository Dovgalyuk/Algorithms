#include <iostream>
#include <vector>
#include <unordered_map>
#include "queue.h"
#include <climits>
#include <algorithm>

using namespace std;

struct Edge {
    int destination;
};

int findShortestPath(const vector<unordered_map<int, Edge>>& graph, int start, int end, vector<int>& previous) {
    vector<int> distance(graph.size(), INT_MAX);
    Queue* q = queue_create();

    distance[start] = 0;
    queue_insert(q, start);

    while (!queue_empty(q)) {
        int current = queue_get(q);
        q.pop();

        for (const auto& neighbor : graph[current]) {
            int newDistance = distance[current] + 1;
            if (newDistance < distance[neighbor.first]) {
                distance[neighbor.first] = newDistance;
                previous[neighbor.first] = current;  // Запоминаем предыдущий узел для восстановления пути
                queue_insert(q, neighbor.first);
            }
        }
    }

    return distance[end];
}

void printPath(const vector<string>& cities, const vector<int>& previous, int start, int end) {
    vector<int> path;
    int current = end;

    while (current != start) {
        path.push_back(current);
        current = previous[current];
    }

    path.push_back(start);

    cout << "Shortest path from " << cities[start] << " to " << cities[end] << " is: ";
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << cities[path[i]];
        if (i != 0) cout << " -> ";
    }

    cout << endl;
}

int main() {
    vector<string> cities;
    vector<unordered_map<int, Edge>> graph;

    string input;
    while (cin >> input && input != "End") {
        if (input == "Start") {
            string city1, city2;
            cin >> city1 >> city2;

            auto it1 = find(cities.begin(), cities.end(), city1);
            auto it2 = find(cities.begin(), cities.end(), city2);

            int index1, index2;

            if (it1 == cities.end()) {
                cities.push_back(city1);
                index1 = cities.size() - 1;
                graph.emplace_back();
            }
            else {
                index1 = distance(cities.begin(), it1);
            }

            if (it2 == cities.end()) {
                cities.push_back(city2);
                index2 = cities.size() - 1;
                graph.emplace_back();
            }
            else {
                index2 = distance(cities.begin(), it2);
            }

            graph[index1][index2] = Edge{ index2 };
        }
    }

    string startCity, endCity;
    cin >> startCity >> endCity;

    int startIndex = distance(cities.begin(), find(cities.begin(), cities.end(), startCity));
    int endIndex = distance(cities.begin(), find(cities.begin(), cities.end(), endCity));

    vector<int> previous(cities.size(), -1);
    int shortestPath = findShortestPath(graph, startIndex, endIndex, previous);

    if (shortestPath != INT_MAX) {
        printPath(cities, previous, startIndex, endIndex);
        cout << "Number of cities to pass through: " << shortestPath << endl;
    }
    else {
        cout << "No path found from " << startCity << " to " << endCity << endl;
    }

    return 0;
}
