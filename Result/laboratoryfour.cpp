//
// Created by KirilliriK on 04.10.2021.
//

#include <random>
#include "directedgraph.h"

const int maxVertices = 4;

int randomInt(int min, int max);

void startDijkstra(DirectedGraph<std::pair<bool, int>> &graph, int vertexIndex);
void findCosts(DirectedGraph<std::pair<bool, int>> &graph, size_t vertexIndex);

int main() {

    int in[maxVertices][maxVertices] = {
        /////0 1 2 3
            {0,3,0,5},
            {0,0,6,1},
            {2,0,0,0},
            {0,0,3,0},
    };

    DirectedGraph<std::pair<bool, int>> graph(maxVertices);
    for (int i = 0; i < maxVertices; i++) {
        graph.setVertex(i, std::pair<bool, int>(false, -1));
        for (int j = 0; j < maxVertices; j++) {
            int cost = in[i][j];
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

void startDijkstra(DirectedGraph<std::pair<bool, int>> &graph, int vertexIndex) {
    for (int i = 0; i < maxVertices; i++) {
        graph.setVertex(i, std::pair<bool, int>(false, -1));
    }
    graph.setVertex(vertexIndex, std::pair<bool, int>(false, 0));

    int lastIndex = vertexIndex;
    while (lastIndex != -1) {
        findCosts(graph, lastIndex);
        lastIndex = -1;
        auto nextIt = graph.getIterator();
        int minCost = -1;
        while (nextIt.hasNext()) {
            nextIt.next();
            auto vertex = *nextIt;
            size_t viewIndex = nextIt.getCurrentIndex();
            if (vertex->data.first) continue;
            if (vertex->data.second == -1) continue;
            if (minCost != -1 && minCost <= vertex->data.second) continue;
            minCost = vertex->data.second;
            lastIndex = viewIndex;
        }
    }

    std::cout << "Cost path from " << vertexIndex << ": " << std::endl;
    for (size_t i = 0; i < maxVertices; i++) {
        if (i == vertexIndex) continue;
        std::cout << "to " << i << " cost is " << graph.getVertex(i)->data.second << std::endl;
    }
    std::cout << std::endl;
}

void findCosts(DirectedGraph<std::pair<bool, int>> &graph, size_t vertexIndex) {
    // Set costs
    auto it = graph.getNeighbourIterator(vertexIndex);
    while (it.hasNext()) {
        it.next();
        auto vertex = *it;
        size_t viewIndex = it.getCurrentIndex();
        int newCost = graph.getEdgeCost(vertexIndex, viewIndex) + graph.getVertex(vertexIndex)->data.second;
        if (vertex->data.first) continue;
        if (vertex->data.second != -1 && vertex->data.second <= newCost) continue;
        vertex->data.second = newCost;
    }
    graph.getVertex(vertexIndex)->data.first = true;
}

int randomInt(int min, int max) {
    std::random_device randomDevice;
    std::mt19937 randomAlgorithm(randomDevice());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(randomAlgorithm);
}
