#include <iostream>
#include <vector>
#include <queue>
#include "graph.h"
#include <climits>

using namespace std;
typedef vector<int> vec;
typedef Graph<int, int> IntGraph;
typedef pair<int, int> IntPair;

vec dijkstra(IntGraph& graph, int startVertexId) {
    const int INF = INT_MAX;
    vec distances(graph.vertexCount(), INF);
    priority_queue<IntPair, vector<IntPair>, greater<>> pq;

    distances[startVertexId] = 0;
    pq.push({ 0, startVertexId });

    while (!pq.empty()) {
        int distance = pq.top().first;
        int vertexId = pq.top().second;
        pq.pop();

        if (distance > distances[vertexId]) continue;

        auto vertex = graph.getVertex(vertexId);
        IntGraph::NeighborIterator neighbors(vertex);
        while (neighbors.hasNext()) {
            auto neighborInfo = neighbors.next();
            int edgeWeight = graph.getEdgeData(neighborInfo.edge); 

            int newDistance = distance + edgeWeight;

            int neighborId = (int)graph.getVertexId(neighborInfo.neighbor);
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
    IntGraph myGraph;

    int vertexCount, edgeCount;
    cout << "Введите количество вершин: ";
    cin >> vertexCount;
    cout << "Введите количество рёбер: ";
    cin >> edgeCount;

    for (int i = 0; i < vertexCount; ++i) {
        myGraph.addVertex(i);
    }

    cout << "Введите ребро в формате from to weight: " << endl;
    for (int i = 0; i < edgeCount; ++i) {
        int fromId, toId, weight;
        cin >> fromId >> toId >> weight;

        IntGraph::Vertex* fromVertex = myGraph.getVertex(fromId);
        IntGraph::Vertex* toVertex = myGraph.getVertex(toId);

        if (fromVertex && toVertex) {
            myGraph.addEdge(fromVertex, toVertex, weight); // Используем указатели на вершины
        }
        else {
            cout << "Одна из вершин не найдена." << endl;
        }
    }

    int startVertex;
    cout << "Введите начальную вершину: ";
    cin >> startVertex;
    vec distances = dijkstra(myGraph, startVertex);

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