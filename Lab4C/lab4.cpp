#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include <climits>

using namespace std;

vector<int> dijkstra(Graph<int, int>& graph, int startVertexId) {
    const int INF = INT_MAX;
    vector<int> distances(graph.vertexCount(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    distances[startVertexId] = 0;
    pq.push({ 0, startVertexId });

    while (!pq.empty()) {
        int distance = pq.top().first;
        int vertexId = pq.top().second;
        pq.pop();

        if (distance > distances[vertexId]) continue;

        // Использование NeighborIterator для перебора соседей
        auto vertex = graph.getVertex(vertexId); // Эту функцию нужно реализовать в классе Graph
        Graph<int, int>::NeighborIterator neighbors(vertex);
        while (neighbors.hasNext()) {
            auto neighbor = neighbors.next();
            int edgeWeight = 1; // Вес ребра
            int newDistance = distance + edgeWeight;

            int neighborId = (int)graph.getVertexId(neighbor); // Эту функцию нужно реализовать в классе Graph
            if (newDistance < distances[neighborId]) {
                distances[neighborId] = newDistance;
                pq.push({ newDistance, neighborId });
            }
        }
    }

    return distances;
}

int main() {
    setlocale(LC_ALL, "rus");
    Graph<int, int> myGraph;

    int vertexCount, edgeCount;
    cout << "Введите количество вершин: ";
    cin >> vertexCount;
    cout << "Введите количество рёбер: ";
    cin >> edgeCount;

    for (int i = 0; i < vertexCount; ++i) {
        myGraph.addVertex(i);
    }

    cout << "Введите ребро в формате from to: " << endl;
    for (int i = 0; i < edgeCount; ++i) {
        int fromId, toId;
        cin >> fromId >> toId;

        Graph<int, int>::Vertex* fromVertex = myGraph.getVertex(fromId);
        Graph<int, int>::Vertex* toVertex = myGraph.getVertex(toId);

        if (fromVertex && toVertex) {
            myGraph.addEdge(fromVertex, toVertex, 1); // Используем указатели на вершины
        }
        else {
            cout << "Одна из вершин не найдена." << endl;
        }
    }

    int startVertex;
    cout << "Введите начальную вершину: ";
    cin >> startVertex;
    vector<int> distances = dijkstra(myGraph, startVertex);

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