﻿
#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include <climits>

using namespace std;
vector<int> dijkstra(Graph& graph, int startVertex) {
    const int INF = INT_MAX;
    vector<int> distances(graph.vertexCount(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    distances[startVertex] = 0;
    pq.push({ 0, startVertex });

    while (!pq.empty()) {
        int distance = pq.top().first;
        int vertex = pq.top().second;
        pq.pop();

        if (distance > distances[vertex]) continue;

        auto neighbors = graph.getNeighbors(vertex);
        while (neighbors.hasNext()) {
            auto neighbor = neighbors.next();
            int edgeWeight = 1;
            int newDistance = distance + edgeWeight;

            if (newDistance < distances[neighbor->id]) {
                distances[neighbor->id] = newDistance;
                pq.push({ newDistance, neighbor->id });
            }
        }
    }

    return distances;
}

int main() {
    setlocale(LC_ALL, "rus");
    Graph graph;
    
    int vertexCount, edgeCount;
    cout << "Введите количество вершин: ";
    cin >> vertexCount;
    cout << "Введите количество рёбер: ";
    cin >>edgeCount;

    for (int i = 0; i < vertexCount; ++i) {
        graph.addVertex(i);
    }
    cout << "Введите ребро в формате from to: " << endl;
    for (int i = 0; i < edgeCount; ++i) {
        int from, to;
        cin >> from >> to;
        graph.addEdge(from, to);
    }

    int startVertex;
    cout << "Введите начальную вершину: ";
    cin >> startVertex;
    vector<int> distances = dijkstra(graph, startVertex);

    for (int i = 0; i < (int)distances.size(); ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Нет пути от вершины " << startVertex << " до вершины " << i << endl;
        }
        else {
            cout << "Кратчайшее расстояние от вершины " << startVertex << " до вершины " << i << " равно " << distances[i] << endl;
        }
    }

    return 0;
}