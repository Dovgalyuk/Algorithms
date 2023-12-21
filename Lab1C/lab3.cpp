#include <iostream>
#include "vector.h"
#include "queue.h"

class Graph {
    int numVertices;
    Vector* adjMatrix;
    Vector* visited;
    Vector* distances;

public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void BFS(int startVertex);
    void printDistances();
};
Graph::~Graph() {
    vector_delete(adjMatrix);
    vector_delete(visited);
    vector_delete(distances);
}

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjMatrix = vector_create();
    vector_resize(adjMatrix, vertices * vertices);
    visited = vector_create();
    vector_resize(visited, vertices);
    distances = vector_create();
    vector_resize(distances, vertices);
}

void Graph::addEdge(int src, int dest) {
    vector_set(adjMatrix, src * numVertices + dest, 1);
}

void Graph::BFS(int startVertex) {
    Queue* queue = queue_create();
    vector_set(visited, startVertex, true);
    queue_insert(queue, startVertex);
    vector_set(distances, startVertex, 0);

    while (!queue_empty(queue)) {
        int currentVertex = queue_get(queue);
        queue_remove(queue);

        for (int adjVertex = 0; adjVertex < numVertices; adjVertex++) {
            if (vector_get(adjMatrix, currentVertex * numVertices + adjVertex) == 1 && !vector_get(visited, adjVertex)) {
                vector_set(visited, adjVertex, true);
                queue_insert(queue, adjVertex);
                vector_set(distances, adjVertex, vector_get(distances, currentVertex) + 1);
            }
        }
    }

    queue_delete(queue);
}

void Graph::printDistances() {
    for (int i = 0; i < numVertices; i++) {
        std::cout << vector_get(distances, i) << std::endl;
    }
}

int main() {
    int numVertices;
    std::cin >> numVertices;

    Graph g(numVertices);

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            int edge;
            std::cin >> edge;
            if (edge == 1) {
                g.addEdge(i, j);
            }
        }
    }

    g.BFS(0);
    g.printDistances();

    return 0;
}