#include <iostream>
#include "directed_graph.h"
#include <string>
#include <unordered_set>

DirectedGraph<int, int>* readGraph() {
    int vertexAmount , edgeAmount;
    std::cin >> vertexAmount >> edgeAmount;
    auto* graph = new DirectedGraph<int, int>(vertexAmount, 1);
    for (int i = 0; i < vertexAmount; ++i) {
        graph->getVertex(i)->data = i;
    }
    for (int i = 0; i < edgeAmount; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph->addEdge(graph->getVertex(from), graph->getVertex(to), i);
    }
    return graph;
}

void detourInDeep(DirectedGraph<int, int>* graph, DirectedGraph<int, int>::Vertex* vertex, bool* was) {
    auto iterator = graph->getNearVertexIterator(vertex);
    while (*iterator) {
        auto* neighbor = (*iterator)->to;
        if (!was[neighbor->data]) {
            was[neighbor->data] = true;
            detourInDeep(graph, neighbor, was);
        }
        iterator++;
    }
}

void fill(bool* array, int size, bool value) {
    for (int i = 0; i < size; ++i) {
        array[i] = value;
    }
}

bool** detourGraph(DirectedGraph<int, int>* graph) {
    auto vertexIterator = graph->getVertexIterator();
    int amount = vertexIterator.amount;
    bool** was = new bool*[amount];
    int i = 0;
    while (*vertexIterator) {
        bool* w = new bool[amount];
        fill(w, amount, false);
        w[i] = true;
        detourInDeep(graph, *vertexIterator, w);
        was[i++] = w;
        vertexIterator++;
    }
    return was;
}

std::string createInt(int* ints, int size) {
    std::string result = "";
    for (int i = 0; i < size; ++i) {
        result += ints[i];
    }
    return result;
}

int main() {
    DirectedGraph<int, int>* graph = readGraph();
    bool** was = detourGraph(graph);
    int amount = graph->getVertexAmount();

    int components[amount][amount];
    for (int j = 0; j < amount; ++j) {
        for (int k = 0; k < amount; ++k) {
            components[j][k] = (was[j][k] * was[k][j]);
        }
    }

    std::unordered_set<std::string> set;
    for (int i = 0; i < amount; ++i) {
        std::string number = createInt(components[i], amount);
        set.insert(number);
    }
    std::cout << "Found strong components of connectivity: " << set.size();

    delete[] was;
    delete graph;
}


/*
5 6
0 1
1 2
1 3
2 0
3 4
4 3

6 6
0 2
2 3
3 5
5 2
1 4
4 1
 */