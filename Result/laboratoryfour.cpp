//
// Created by KirilliriK on 04.10.2021.
//

#include <random>
#include "directedgraph.h"

const int maxVertices = 4;

int randomInt(int min, int max);

void startDijkstra(DirectedGraph<int> &graph, int vertexIndex);
void findCosts(DirectedGraph<int> &graph, size_t vertexIndex, std::vector<bool> &visited, std::vector<int> &costs);

int main() {

    int in[maxVertices][maxVertices] = {
        /////0 1 2 3
            {0,3,0,5},
            {0,0,6,1},
            {2,0,0,0},
            {0,0,3,0},
    };

    DirectedGraph<int> graph(maxVertices);
    for (int i = 0; i < maxVertices; i++) {
        graph.setVertex(i, i);
        for (int j = 0; j < maxVertices; j++) {
            int cost = in[i][j];
            if (cost == 0) continue;
            graph.setEdge(i, j, cost);
        }
    }

    graph.displayMatrix();

    std::cout << std::endl;

    for (int i = 0; i < maxVertices; i++) {
        startDijkstra(graph, i);
    }

    return 0;
}

void startDijkstra(DirectedGraph<int> &graph, int vertexIndex) {
    size_t vertexCount = graph.getVertexCount();
    std::vector<bool> visited;
    visited.resize(vertexCount);
    std::vector<int> costs;
    costs.resize(vertexCount);
    for (size_t i = 0; i < vertexCount; i++) {
        visited[i] = false;
        if (i == vertexIndex) {
            costs[i] = 0;
            continue;
        }
        costs[i] = -1;
    }

    findCosts(graph, vertexIndex, visited, costs);

    std::cout << "Cost path from " << vertexIndex << ": " << std::endl;
    for (size_t i = 0; i < maxVertices; i++) {
        if (i == vertexIndex) continue;
        std::cout << "to " << i << " cost is " << costs[i] << std::endl;
    }
    std::cout << std::endl;
}

void findCosts(DirectedGraph<int> &graph, size_t vertexIndex, std::vector<bool> &visited, std::vector<int> &costs) {
    // Set costs
    auto it = graph.getNeighbourIterator(vertexIndex);
    while (it.hasNext()) {
        it.next();
        size_t viewIndex = it.getCurrentIndex();
        int newCost = graph.getEdgeCost(vertexIndex, viewIndex) + costs[vertexIndex];
        if (visited[viewIndex]) continue;
        if (costs[viewIndex] != -1 && costs[viewIndex] <= newCost) continue;
        costs[viewIndex] = newCost;
    }
    visited[vertexIndex] = true;

    // Find next
    auto nextIt = graph.getIterator();
    int minCost = -1;
    int lastIndex = -1;
    while (nextIt.hasNext()) {
        nextIt.next();
        size_t viewIndex = nextIt.getCurrentIndex();
        if (visited[viewIndex]) continue;
        if (costs[viewIndex] == -1) continue;
        if (minCost != -1 && minCost <= costs[viewIndex]) continue;
        minCost = costs[viewIndex];
        lastIndex = viewIndex;
    }

    if (lastIndex == -1) return;

    findCosts(graph, lastIndex, visited, costs);
}

int randomInt(int min, int max) {
    std::random_device randomDevice;
    std::mt19937 randomAlgorithm(randomDevice());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(randomAlgorithm);
}
