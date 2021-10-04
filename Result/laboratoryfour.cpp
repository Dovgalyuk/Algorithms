//
// Created by KirilliriK on 04.10.2021.
//

#include <random>
#include "directedgraph.h"

const int maxVertices = 4;

int randomInt(int min, int max);
void findPathCosts(DirectedGraph<bool> &graph, int vertexIndex);
void fillCosts(DirectedGraph<bool> &graph, std::vector<int> &costPath, std::vector<int> &nextVertices, int ownerVertexIndex);

int main() {

    int in[maxVertices][maxVertices] = {
        /////0 1 2 3
            {0,3,0,5},
            {0,0,6,1},
            {2,0,0,0},
            {0,0,3,0},
    };

    DirectedGraph<bool> graph(maxVertices);
    for (int i = 0; i < maxVertices; i++) {
        for (int j = 0; j < maxVertices; j++) {
            graph.setVertex(i + j * maxVertices, true);

            int cost = in[i][j];
            if (cost == 0) continue;
            graph.setEdge(i, j, cost);
        }
    }
    for (int i = 0; i < maxVertices; i++) {
        findPathCosts(graph, i);
    }
    system("pause");
    return 0;
}

void findPathCosts(DirectedGraph<bool> &graph, int vertexIndex) {
    std::vector<int> costPath;
    costPath.reserve(maxVertices);
    for (int i = 0; i < maxVertices; i++) {
        costPath.push_back(0);
    }
    std::vector<int> currentVertices;
    std::vector<int> nextVertices;
    nextVertices.push_back(vertexIndex);
    while(!nextVertices.empty()) {
        currentVertices = nextVertices;
        nextVertices.clear();
        for (int i: currentVertices) {
            fillCosts(graph, costPath, nextVertices, i);
        }
    }

    std::cout << "Cost path from " << vertexIndex << ": " << std::endl;
    for (int i = 0; i < maxVertices; i++) {
        if (i == vertexIndex) continue;
        std::cout << "to " << i << " cost is " << costPath[i] << std::endl;
    }
    std::cout << std::endl;
}

void fillCosts(DirectedGraph<bool> &graph, std::vector<int> &costPath, std::vector<int> &nextVertices, int ownerVertexIndex) {
    int ownerVertexCost = costPath[ownerVertexIndex];
    for (int i: graph.getLinkedVertices(ownerVertexIndex)) {
        int newCost = graph.getEdgeCost(ownerVertexIndex, i) + ownerVertexCost;
        if (newCost == 0 || (costPath[i] != 0 && costPath[i] <= newCost)) continue;
        costPath[i] = newCost;
        nextVertices.push_back(i);
    }
}

int randomInt(int min, int max) {
    std::random_device randomDevice;
    std::mt19937 randomAlgorithm(randomDevice());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(randomAlgorithm);
}
