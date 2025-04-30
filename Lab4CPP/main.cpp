#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include "graph.h"

typedef Graph<std::string, int> MyGraph;

struct Edge {
    size_t from;
    size_t to;
    int weight;

    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

void PrimMST(const MyGraph& graph) {
    size_t vertexCount = graph.VertexCount();
    if (vertexCount == 0) {
        std::cout << "Граф пустой.\n";
        return;
    }

    Vector<bool> inMST(vertexCount, false); 
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

    inMST.set(0, true);
    auto initialNeighbors = graph.GetNeighbors(0); 
    for (size_t i = 0; i < initialNeighbors.size(); ++i) {
        size_t neighbor = initialNeighbors.get(i);
        auto weight = graph.GetEdgeLabel(0, neighbor);
        if (weight.has_value()) {
            pq.push({0, neighbor, weight.value()});
        }
    }

    int mstWeight = 0;
    std::vector<Edge> mstEdges;

    while (!pq.empty()) {
        Edge edge = pq.top();
        pq.pop();

        if (inMST.get(edge.to)) continue;

        inMST.set(edge.to, true);
        mstWeight += edge.weight;
        mstEdges.push_back(edge);

        auto currentNeighbors = graph.GetNeighbors(edge.to); 
        for (size_t i = 0; i < currentNeighbors.size(); ++i) {
            size_t neighbor = currentNeighbors.get(i);
            if (!inMST.get(neighbor)) {
                auto weight = graph.GetEdgeLabel(edge.to, neighbor);
                if (weight.has_value()) {
                    pq.push({edge.to, neighbor, weight.value()});
                }
            }
        }
    }

    std::cout << "Минимальный вес связующего дерева: " << mstWeight << "\n";
    std::cout << "Ребра в MST:\n";
    for (const auto& edge : mstEdges) {
        std::cout << edge.from << " - " << edge.to << " (вес: " << edge.weight << ")\n";
    }
}

int main(int argc, char* argv[]) {
    std::istream* input = &std::cin;
    std::ifstream inputFile;

    if (argc >= 2) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            std::cerr << "Ошибка: не удалось открыть файл " << argv[1] << std::endl;
            return 1;
        }
        input = &inputFile;
    }

    size_t vertexCount;
    *input >> vertexCount;

    MyGraph graph(vertexCount);

    size_t from, to;
    int weight;
    while (*input >> from >> to >> weight) {
        graph.AddEdge(from, to, weight);
        graph.AddEdge(to, from, weight); 
    }

    PrimMST(graph);

    return 0;
}